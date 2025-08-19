# MyBlog - Hexo Static Blog

This repository contains Azusayn's personal blog built with Hexo.

## GitHub Pages Deployment

The blog is automatically deployed to GitHub Pages when changes are pushed to the `blog_0.2.0` branch.

### Access

- **Live Site**: https://azusain.github.io/blog
- **Base Path**: `/blog`

### Setup

1. Enable GitHub Pages in repository settings
2. Set source to "GitHub Actions"
3. Push changes to `blog_0.2.0` branch to trigger deployment

### Local Development

```bash
cd blog_0.2.0
npm install
npm run server  # Start development server
npm run build   # Generate static files
```

### Project Structure

- `blog_0.2.0/` - Main Hexo blog directory
- `source/_posts/` - Blog posts organized by categories
- `themes/next/` - Next.js theme
- `.github/workflows/deploy.yml` - GitHub Actions deployment workflow
