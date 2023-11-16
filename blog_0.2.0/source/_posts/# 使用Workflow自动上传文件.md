---
title:  使用Workflow自动上传文件
date: 2023/7/27 15:21:00
categories:
- workflow
tags:
- github
- workflow
---
### 基本操作流程

* 设置服务器地址、用户名、密码和远程路径
```shell
    SERVER="your_server"
    USERNAME="your_username"
    PASSWORD="your_password"
    REMOTE_PATH="/path/to/remote/folder"
```
* 设置本地文件夹路径
```shell
	LOCAL_FOLDER_PATH="/path/to/local/folder"
```
* 使用 scp 命令上传文件夹
```shell
sshpass -p "$PASSWORD" scp -r "$LOCAL_FOLDER_PATH""$USERNAME@$SERVER:$REMOTE_PATH"
```

* 您可以使用 `GitHub Secrets` 来安全地存储敏感信息，例如密码、密钥或访问令牌等。下面是一个简单的例子，它演示了如何在工作流中使用 `GitHub Secrets` 来存储和使用 `SSH` 密码。

1. 在您的 GitHub 仓库中，导航到 `Settings` 选项卡，然后单击 `Secrets`。
2. 单击 `New repository secret` 按钮，然后输入一个名称（例如 `SSH_PASSWORD`）和您的 `SSH` 密码。单击 `Add secret` 按钮保存您的密钥。
3. 在您的工作流文件中，您可以使用 `${{ secrets.SSH_PASSWORD }}` 来引用您刚才存储的密钥。例如：

```yaml
jobs:
  upload:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v2

      - name: Upload folder to server
        run: |
          # 设置服务器地址、用户名和远程路径
          SERVER="your_server"
          USERNAME="your_username"
          REMOTE_PATH="/path/to/remote/folder"

          # 设置本地文件夹路径
          LOCAL_FOLDER_PATH="/path/to/local/folder"

          # 安装 sshpass
          sudo apt-get update
          sudo apt-get install -y sshpass

          # 使用 scp 命令上传文件夹
          sshpass -p ${{ secrets.SSH_PASSWORD }} scp -r "$LOCAL_FOLDER_PATH" "$USERNAME@$SERVER:$REMOTE_PATH"
```

### 注解
* 在上面的示例中，我们使用 `${{ secrets.SSH_PASSWORD }}` 来引用存储在 `GitHub Secrets` 中的 `SSH` 密码。这样，我们就可以在工作流中安全地使用这个密码，而不必担心泄露敏感信息。`actions/checkout@v2` 是一个 `GitHub Action`，它可以检出您的仓库代码。它的工作原理是使用 `git` 命令来克隆您的仓库到工作流运行环境中。默认情况下，它只会获取触发工作流的那个 `ref/SHA` 的单个提交。但您也可以通过设置 `fetch-depth: 0` 来获取所有分支和标签的所有历史记录¹。

* 此外，这个 `Action` 还会将身份验证令牌持久化到本地 `git` 配置中。这样，您的脚本就可以运行经过身份验证的 `git` 命令。在后续步骤中，该令牌会在后置作业清理期间被删除。您可以通过设置 `persist-credentials: false` 来选择退出¹。简而言之，`actions/checkout@v2` 能够检出您的代码，是因为它使用了 `git` 命令来克隆您的仓库，并将身份验证令牌持久化到本地 `git` 配置中。希望这对您有所帮助！

* 在上面给出的 `shell` 脚本示例中，我们使用了 `sshpass` 命令来非交互式地提供 `SSH` 密码。这样，我们就可以在脚本中使用 `scp` 命令来上传文件夹，而不需要手动输入密码。如果您直接使用 `scp` 命令，那么在执行命令时，系统会提示您输入密码。这在交互式环境中是可以的，但在脚本中就不太方便了。为了避免这种情况，我们使用了 `sshpass` 命令来非交互式地提供密码。当然，除了使用密码登录，您还可以使用 `SSH` 密钥来进行身份验证。这种方法更安全，也更方便。如果您希望使用 `SSH` 密钥来进行身份验证，那么您就不需要使用 `sshpass` 命令了。

