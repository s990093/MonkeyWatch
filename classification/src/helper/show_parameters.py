from rich.console import Console
from rich.table import Table


def show_parameters(data, model, epochs, imgsz, batch_size, device):
    """使用 Rich 顯示訓練參數"""
    console = Console()

    table = Table(title="訓練參數設定", show_header=True, header_style="bold magenta")
    table.add_column("參數", style="cyan")
    table.add_column("數值", style="green")

    parameters = {
        "資料集路徑": data,
        "模型": model,
        "訓練回合": str(epochs),
        "圖片大小": str(imgsz),
        "批次大小": str(batch_size),
        "設備": device,
    }

    for param, value in parameters.items():
        table.add_row(param, value)

    console.print("\n")
    console.print(table)
    console.print("\n")