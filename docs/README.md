# MyBlog - Hexo Static Blog

This repository contains Azusayn's personal blog built with Hexo.

## GitHub Pages Deployment

The blog is automatically deployed to GitHub Pages when changes are pushed to the `blog_0.2.0` branch.

### Access

- **Live Site**: https://azusain.github.io/blog
- **Base Path**: `/blog`

### Manual Setup Required

**IMPORTANT**: You must manually enable GitHub Pages first:

1. Go to your repository: https://github.com/Azusain/MyBlog
2. Click **Settings** tab
3. Scroll down to **Pages** section (left sidebar)
4. Under "Source", select **GitHub Actions**
5. Save the settings
6. Push changes to `blog_0.2.0` branch to trigger deployment

**Why manual setup?** GitHub Actions needs additional permissions to automatically create Pages sites. Manual setup avoids permission issues.

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
