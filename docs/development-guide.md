# Development Guide

This guide covers local development workflow, available commands, and project structure for the MyBlog Hexo site.

## Project Structure

```
MyBlog/
├── .github/
│   └── workflows/
│       └── deploy.yml          # GitHub Actions deployment
├── blog_0.2.0/                 # Main Hexo blog directory
│   ├── _config.yml             # Hexo configuration
│   ├── package.json            # Node.js dependencies and scripts
│   ├── source/                 # Blog content
│   │   ├── _posts/             # Blog posts
│   │   ├── CNAME               # Custom domain file (auto-generated)
│   │   └── uploads/            # Static assets
│   ├── themes/
│   │   └── next/               # Next.js theme (Git submodule)
│   └── scripts/
│       └── switch-domain.js    # Domain switching utility
├── docs/                       # Documentation
└── scripts/                    # Root-level utilities
```

## Quick Start

### Initial Setup
```bash
# Clone repository with submodules
git clone --recursive https://github.com/Azusain/MyBlog.git
cd MyBlog/blog_0.2.0

# Install dependencies
npm install
```

### Development Workflow
```bash
# Start development server
npm run dev

# Build static files
npm run build

# Clean generated files
npm run clean
```

## Available Commands

### Core Commands
| Command | Description |
|---------|-------------|
| `npm run dev` | Start local development server at http://localhost:4000 |
| `npm run build` | Generate static files for production |
| `npm run clean` | Remove generated files and cache |
| `npm run server` | Alias for `npm run dev` |
| `npm start` | Alias for `npm run dev` |

### Domain Management
| Command | Description |
|---------|-------------|
| `npm run domain:github` | Switch to GitHub Pages domain and rebuild |
| `npm run domain:custom` | Switch to custom domain (azusayn.site) and rebuild |
| `npm run domain:switch` | Show available domain options |

### Domain Switching Details

#### GitHub Pages Mode
- **URL**: `https://azusain.github.io/MyBlog`
- **Base Path**: `/MyBlog/`
- **CNAME File**: Removed
- **Use Case**: Default GitHub Pages deployment

#### Custom Domain Mode  
- **URL**: `https://azusayn.site`
- **Base Path**: `/`
- **CNAME File**: Created with `azusayn.site`
- **Use Case**: Custom domain with DNS configuration

## Content Management

### Creating New Posts
```bash
# Navigate to blog directory
cd blog_0.2.0

# Generate new post
npx hexo new post "Your Post Title"

# Edit the generated file in source/_posts/
```

### Post Front Matter
```yaml
---
title: Your Post Title
date: 2025-01-01 12:00:00
categories:
- Category Name
tags:
- tag1
- tag2
---

Your post content here...
```

### Categories and Tags
The blog supports multiple categories and tags:

**Existing Categories:**
- C/C++
- Deep Learning (DL)
- Frontend
- UNIX
- Workflow

**Common Tags:**
- C/C++, CMake, NetWork, shell
- Deep Learning
- HTML, CSS, JavaScript, TypeScript, web
- UNIX, workflow, github

## Theme Configuration

The blog uses [hexo-theme-next](https://github.com/next-theme/hexo-theme-next) as a Git submodule.

### Updating Theme
```bash
cd blog_0.2.0/themes/next
git pull origin master
cd ../..
git add themes/next
git commit -m "Update Next theme"
```

### Theme Customization
Theme settings are configured in `blog_0.2.0/_config.yml` under the theme section.

## Deployment

### Automatic Deployment
- Pushes to `main` branch trigger GitHub Actions
- Workflow builds and deploys to GitHub Pages
- Supports both GitHub Pages and custom domain modes

### Manual Deployment Testing
```bash
# Build locally
npm run build

# Check generated files
ls public/

# Verify index.html exists and has content
cat public/index.html
```

## Git Workflow

### Recommended Workflow
```bash
# Create feature branch
git checkout -b feature/new-post

# Make changes
# ... edit files ...

# Commit changes
git add .
git commit -m "Add new blog post about X"

# Push and create PR
git push origin feature/new-post
```

### Submodule Management
```bash
# Initialize submodules (first time)
git submodule update --init --recursive

# Update submodules
git submodule update --remote

# Commit submodule updates
git add .gitmodules themes/next
git commit -m "Update theme submodule"
```

## Troubleshooting

### Common Issues

**Build Fails with Theme Error:**
```bash
# Ensure submodules are initialized
git submodule update --init --recursive
```

**Local Server Not Starting:**
```bash
# Clear cache and reinstall
npm run clean
rm -rf node_modules
npm install
npm run dev
```

**Domain Switching Not Working:**
```bash
# Manual domain switch if npm script fails
node scripts/switch-domain.js custom
npm run build
```

**GitHub Actions Deployment Fails:**
- Check Actions logs in GitHub repository
- Ensure all submodules are properly committed
- Verify package.json and _config.yml syntax

### Debug Commands
```bash
# Check Hexo configuration
npx hexo config

# List all posts
npx hexo list post

# Generate with verbose output
npx hexo generate --debug
```

## Performance Optimization

### Build Optimization
- Use `npm run clean` before important builds
- Keep `node_modules/` in `.gitignore`
- Optimize images in `source/uploads/`

### Theme Performance
- Minimize custom CSS/JS modifications
- Use CDN links for external libraries
- Enable compression in deployment

## Contributing

### Code Style
- Use English for commit messages and documentation
- Follow existing code formatting
- Test domain switching before committing
- Verify builds work locally before pushing

### Pull Request Process
1. Create feature branch from `main`
2. Make changes and test locally
3. Update documentation if needed
4. Create pull request with clear description
5. Ensure CI passes before merging
