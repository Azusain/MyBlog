# Domain switching script for MyBlog
# Usage: .\switch-domain.ps1 -Domain "github" or .\switch-domain.ps1 -Domain "custom"

param(
    [Parameter(Mandatory=$true)]
    [ValidateSet("github", "custom")]
    [string]$Domain
)

$configFile = "blog_0.2.0/_config.yml"
$cnameFile = "blog_0.2.0/source/CNAME"
$cnameExample = "blog_0.2.0/source/CNAME.example"

if ($Domain -eq "github") {
    Write-Host "Switching to GitHub Pages domain..." -ForegroundColor Green
    
    # Update _config.yml for GitHub Pages
    $config = Get-Content $configFile -Raw
    $config = $config -replace 'url: https://azusayn\.site', 'url: https://azusain.github.io/MyBlog'
    $config = $config -replace 'root: /', 'root: /MyBlog/'
    $config = $config -replace '# url: https://azusain\.github\.io/MyBlog', 'url: https://azusain.github.io/MyBlog'
    $config = $config -replace '# root: /MyBlog/', 'root: /MyBlog/'
    $config = $config -replace 'url: https://azusayn\.site', '# url: https://azusayn.site'
    $config = $config -replace 'root: /', '# root: /'
    Set-Content $configFile $config
    
    # Remove CNAME file if exists
    if (Test-Path $cnameFile) {
        Remove-Item $cnameFile
        Write-Host "Removed CNAME file" -ForegroundColor Yellow
    }
    
    Write-Host "Configured for GitHub Pages: https://azusain.github.io/MyBlog" -ForegroundColor Green
}
elseif ($Domain -eq "custom") {
    Write-Host "Switching to custom domain..." -ForegroundColor Green
    
    # Update _config.yml for custom domain
    $config = Get-Content $configFile -Raw
    $config = $config -replace 'url: https://azusain\.github\.io/MyBlog', '# url: https://azusain.github.io/MyBlog'
    $config = $config -replace 'root: /MyBlog/', '# root: /MyBlog/'
    $config = $config -replace '# url: https://azusayn\.site', 'url: https://azusayn.site'
    $config = $config -replace '# root: /', 'root: /'
    Set-Content $configFile $config
    
    # Create CNAME file
    if (Test-Path $cnameExample) {
        Copy-Item $cnameExample $cnameFile
        Write-Host "Created CNAME file" -ForegroundColor Yellow
    }
    
    Write-Host "Configured for custom domain: https://azusayn.site" -ForegroundColor Green
    Write-Host "Don't forget to:" -ForegroundColor Yellow
    Write-Host "1. Configure DNS records for azusayn.site" -ForegroundColor Yellow
    Write-Host "2. Enable custom domain in GitHub Pages settings" -ForegroundColor Yellow
}

Write-Host "Run 'npm run build' to rebuild with new configuration" -ForegroundColor Cyan
