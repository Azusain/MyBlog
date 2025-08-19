# Custom Domain Configuration Guide

This guide explains how to configure your custom domain `azusayn.site` for GitHub Pages deployment.

## Prerequisites

- Domain purchased and access to DNS management
- GitHub Pages enabled for this repository
- Blog already deployed via GitHub Actions

## DNS Configuration

Configure the following DNS records with your domain registrar:

### A Records (Required)

Point your apex domain to GitHub Pages servers:

| Name | Type | Value |
|------|------|-------|
| @ | A | 185.199.108.153 |
| @ | A | 185.199.109.153 |
| @ | A | 185.199.110.153 |
| @ | A | 185.199.111.153 |

### AAAA Records (Optional, for IPv6)

| Name | Type | Value |
|------|------|-------|
| @ | AAAA | 2606:50c0:8000::153 |
| @ | AAAA | 2606:50c0:8001::153 |
| @ | AAAA | 2606:50c0:8002::153 |
| @ | AAAA | 2606:50c0:8003::153 |

## GitHub Pages Setup

1. Navigate to repository settings: https://github.com/Azusain/MyBlog/settings/pages
2. Under "Custom domain", enter: `azusayn.site`
3. Click **Save**
4. Wait for DNS check to complete (may take up to 24 hours)
5. Once verified, enable **"Enforce HTTPS"**

## Verification Steps

### 1. DNS Propagation Check
```bash
# Check A records
nslookup azusayn.site

# Expected output should include GitHub Pages IPs
```

### 2. GitHub Pages Status
- Green checkmark next to custom domain in repository settings
- "DNS check successful" message

### 3. Website Access
- Visit `https://azusayn.site`
- Verify SSL certificate is valid
- Check that all assets load correctly

## Troubleshooting

### Common Issues

**DNS not propagating:**
- Wait 24-48 hours for full propagation
- Clear browser DNS cache
- Use different DNS lookup tools to verify

**GitHub Pages not recognizing domain:**
- Ensure CNAME file exists in repository
- Check that DNS A records point to correct IPs
- Verify domain is spelled correctly

**SSL certificate issues:**
- Wait for GitHub to provision certificate (up to 24 hours)
- Ensure "Enforce HTTPS" is only enabled after SSL is ready

### DNS Providers Examples

#### Cloudflare
1. Login to Cloudflare dashboard
2. Select your domain
3. Go to DNS → Records
4. Add A records as specified above
5. Set Proxy status to "DNS only" (gray cloud)

#### Namecheap
1. Login to Namecheap account
2. Go to Domain List → Manage
3. Advanced DNS tab
4. Add A records as specified above

#### GoDaddy
1. Login to GoDaddy account
2. My Products → DNS
3. Add A records as specified above

## Domain Switching

### Switch to Custom Domain
```bash
cd blog_0.2.0
npm run domain:custom
git add .
git commit -m "Switch to custom domain"
git push
```

### Switch back to GitHub Pages
```bash
cd blog_0.2.0
npm run domain:github
git add .
git commit -m "Switch back to GitHub Pages"
git push
```

## Configuration Files

The following files are automatically managed during domain switching:

- `blog_0.2.0/_config.yml` - Hexo configuration with URL and root path
- `blog_0.2.0/source/CNAME` - GitHub Pages custom domain file

## Timeline

| Step | Expected Time |
|------|---------------|
| DNS record creation | Immediate |
| DNS propagation | 10 minutes - 48 hours |
| GitHub Pages recognition | 5-60 minutes after DNS |
| SSL certificate provisioning | 5 minutes - 24 hours |

## Support

For issues with:
- **DNS configuration**: Contact your domain registrar
- **GitHub Pages**: Check [GitHub Pages documentation](https://docs.github.com/en/pages)
- **Blog deployment**: Check GitHub Actions logs in repository
