import subprocess
import sys

# 嘗試導入 rich，如果失敗則安裝
try:
    from rich.progress import Progress
except ImportError:
    print("rich is not installed. Installing...")
    if not subprocess.check_call([sys.executable, "-m", "pip", "install", "rich"]):
        # print("Failed to install ri/ch. Please install it manually.")
        pass
        # sys.exit(1)
    from rich.progress import Progress  # 成功安裝後再次導入

def install(package):
    try:
        # Redirecting stdout and stderr to suppress installation output
        subprocess.check_call([sys.executable, "-m", "pip", "install", package], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        return True
    except subprocess.CalledProcessError:
        return False

def main():
    # 讀取 requirements.txt 中的包
    with open("requirements.txt", "r") as file:
        packages = [pkg.strip() for pkg in file.readlines() if pkg.strip()]

    total_packages = len(packages)
    
    with Progress() as progress:
        task = progress.add_task("[green]Installing packages...", total=total_packages)
        
        for package in packages:
            if install(package):
                progress.console.print(f"[green]Successfully installed {package}")
            else:
                progress.console.print(f"[red]Failed to install {package}")
            progress.update(task, advance=1)

        progress.console.print("[blue]Installation completed.")

if __name__ == "__main__":
    main()