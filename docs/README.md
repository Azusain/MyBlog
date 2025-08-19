# MyBlog - Hexo Static Blog

This repository contains Azusayn's personal blog built with Hexo.

## GitHub Pages Deployment

The blog is automatically deployed to GitHub Pages when changes are pushed to the `main` branch.

### Access

- **Live Site**: https://azusain.github.io/MyBlog
- **Base Path**: `/MyBlog`

### Manual Setup Required

**IMPORTANT**: You must manually enable GitHub Pages first:

1. Go to your repository: https://github.com/Azusain/MyBlog
2. Click **Settings** tab
3. Scroll down to **Pages** section (left sidebar)
4. Under "Source", select **GitHub Actions**
5. Save the settings
6. Push changes to `main` branch to trigger deployment

**Why manual setup?** GitHub Actions needs additional permissions to automatically create Pages sites. Manual setup avoids permission issues.

### Local Development

```bash
cd blog_0.2.0
npm install
npm run dev     # Start development server
npm run build   # Generate static files
npm run clean   # Clean generated files
```

### Domain Switching

This blog supports both GitHub Pages and custom domains:

**Current setup**: GitHub Pages (`https://azusain.github.io/MyBlog`)

#### Switch to Custom Domain (azusayn.site)

```bash
cd blog_0.2.0
npm run domain:custom
```

#### Switch back to GitHub Pages

```bash
cd blog_0.2.0
npm run domain:github
```

#### Show available domains

```bash
cd blog_0.2.0
npm run domain:switch
```

#### Custom Domain Setup Steps

1. **DNS Configuration**: Point your domain to GitHub Pages
   ```
   # A records
   185.199.108.153
   185.199.109.153
   185.199.110.153
   185.199.111.153
   
   # Or CNAME (for subdomain)
   azusain.github.io
   ```

2. **Switch domain and rebuild**:
   ```bash
   cd blog_0.2.0
   npm run domain:custom
   ```

3. **Commit and push**:
   ```bash
   git add .
   git commit -m "Switch to custom domain"
   git push
   ```

4. **Enable in GitHub Pages settings**:
   - Go to repository Settings → Pages
   - Enter custom domain: `azusayn.site`
   - Enable "Enforce HTTPS"

### Project Structure

- `blog_0.2.0/` - Main Hexo blog directory
- `source/_posts/` - Blog posts organized by categories
- `themes/next/` - Next.js theme
- `.github/workflows/deploy.yml` - GitHub Actions deployment workflow
- `scripts/switch-domain.ps1` - Domain switching utility
