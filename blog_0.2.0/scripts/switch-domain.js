#!/usr/bin/env node

const fs = require('fs');
const path = require('path');

// Configuration
const CONFIG = {
  configFile: '_config.yml',
  cnameFile: 'source/CNAME',
  cnameExample: 'source/CNAME.example',
  domains: {
    github: {
      url: 'https://azusain.github.io/MyBlog',
      root: '/MyBlog/',
      description: 'GitHub Pages'
    },
    custom: {
      url: 'https://azusayn.site',
      root: '/',
      description: 'Custom Domain (azusayn.site)'
    }
  }
};

function main() {
  const args = process.argv.slice(2);
  const domain = args[0];

  if (!domain || !CONFIG.domains[domain]) {
    console.log('Usage: node scripts/switch-domain.js [github|custom]');
    console.log('');
    console.log('Available domains:');
    Object.keys(CONFIG.domains).forEach(key => {
      console.log(`  ${key}: ${CONFIG.domains[key].description}`);
    });
    process.exit(1);
  }

  switchDomain(domain);
}

function switchDomain(targetDomain) {
  const target = CONFIG.domains[targetDomain];
  
  console.log(`\n🔄 Switching to ${target.description}...`);
  
  try {
    // Update _config.yml
    updateHexoConfig(targetDomain, target);
    
    // Handle CNAME file
    updateCnameFile(targetDomain);
    
    console.log(`\n✅ Successfully switched to ${target.description}`);
    console.log(`📍 URL: ${target.url}`);
    console.log(`📁 Root: ${target.root}`);
    
    if (targetDomain === 'custom') {
      console.log(`\n⚠️  Don't forget to:`);
      console.log(`   1. Configure DNS records for azusayn.site`);
      console.log(`   2. Enable custom domain in GitHub Pages settings`);
    }
    
    console.log(`\n🔨 Run 'npm run build' to rebuild with new configuration`);
    
  } catch (error) {
    console.error(`\n❌ Error switching domain: ${error.message}`);
    process.exit(1);
  }
}

function updateHexoConfig(targetDomain, target) {
  if (!fs.existsSync(CONFIG.configFile)) {
    throw new Error(`Configuration file ${CONFIG.configFile} not found`);
  }
  
  let config = fs.readFileSync(CONFIG.configFile, 'utf8');
  
  // Comment out all URL and root configurations first
  config = config.replace(/^url: https:\/\/azusain\.github\.io\/MyBlog$/m, '# url: https://azusain.github.io/MyBlog');
  config = config.replace(/^root: \/MyBlog\/$/m, '# root: /MyBlog/');
  config = config.replace(/^url: https:\/\/azusayn\.site$/m, '# url: https://azusayn.site');
  config = config.replace(/^root: \/$/m, '# root: /');
  
  // Uncomment and set the target configuration
  if (targetDomain === 'github') {
    config = config.replace(/^# url: https:\/\/azusain\.github\.io\/MyBlog$/m, 'url: https://azusain.github.io/MyBlog');
    config = config.replace(/^# root: \/MyBlog\/$/m, 'root: /MyBlog/');
  } else if (targetDomain === 'custom') {
    config = config.replace(/^# url: https:\/\/azusayn\.site$/m, 'url: https://azusayn.site');
    config = config.replace(/^# root: \/$/m, 'root: /');
  }
  
  fs.writeFileSync(CONFIG.configFile, config);
  console.log(`📝 Updated ${CONFIG.configFile}`);
}

function updateCnameFile(targetDomain) {
  if (targetDomain === 'custom') {
    // Create CNAME file for custom domain
    if (fs.existsSync(CONFIG.cnameExample)) {
      fs.copyFileSync(CONFIG.cnameExample, CONFIG.cnameFile);
      console.log(`📄 Created ${CONFIG.cnameFile}`);
    } else {
      // Create CNAME file directly
      fs.writeFileSync(CONFIG.cnameFile, 'azusayn.site\n');
      console.log(`📄 Created ${CONFIG.cnameFile}`);
    }
  } else {
    // Remove CNAME file for GitHub Pages
    if (fs.existsSync(CONFIG.cnameFile)) {
      fs.unlinkSync(CONFIG.cnameFile);
      console.log(`🗑️  Removed ${CONFIG.cnameFile}`);
    }
  }
}

if (require.main === module) {
  main();
}

module.exports = { switchDomain };
