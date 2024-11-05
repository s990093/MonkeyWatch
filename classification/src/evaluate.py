from ultralytics import YOLO
import click
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from pathlib import Path

@click.command()
@click.option('--model-path', 
              default='runs/detect/train/weights/best.pt',
              help='訓練完成的模型權重路徑')
@click.option('--data', 
              default='/Users/hungwei/Desktop/Proj/Monkey/dataset/data.yaml',
              help='資料集配置文件路徑')
@click.option('--device', 
              default='mps', 
              help='使用的設備 ("mps" for Apple Silicon GPU, "cpu" for CPU)')
def evaluate_model(model_path, data, device):
    # 載入訓練好的模型
    model = YOLO(model_path)
    
    # 在驗證集上評估模型
    results = model.val(data=data, device=device)
    
    # 創建結果保存目錄
    save_dir = Path('evaluation_results')
    save_dir.mkdir(exist_ok=True)
    
    # 獲取評估指標
    metrics = results.results_dict
    
    # 顯示並保存主要指標
    metrics_summary = {
        'mAP50': metrics['metrics/mAP50(B)'],
        'mAP50-95': metrics['metrics/mAP50-95(B)'],
        'Precision': metrics['metrics/precision(B)'],
        'Recall': metrics['metrics/recall(B)'],
        'F1-Score': metrics['metrics/F1(B)']
    }
    
    # 將指標保存到文件
    with open(save_dir / 'metrics_summary.txt', 'w') as f:
        for metric_name, value in metrics_summary.items():
            print(f"{metric_name}: {value:.4f}")
            f.write(f"{metric_name}: {value:.4f}\n")
    
    # 繪製混淆矩陣
    if hasattr(results, 'confusion_matrix'):
        plt.figure(figsize=(10, 8))
        sns.heatmap(results.confusion_matrix.matrix, 
                    annot=True, 
                    fmt='d',
                    cmap='Blues')
        plt.title('Confusion Matrix')
        plt.xlabel('Predicted')
        plt.ylabel('True')
        plt.savefig(save_dir / 'confusion_matrix.png')
        plt.close()
    
    # 如果有PR曲線數據，繪製PR曲線
    if hasattr(results, 'pr_curve'):
        plt.figure(figsize=(10, 6))
        plt.plot(results.pr_curve[:, 1], results.pr_curve[:, 0])
        plt.xlabel('Recall')
        plt.ylabel('Precision')
        plt.title('Precision-Recall Curve')
        plt.grid(True)
        plt.savefig(save_dir / 'pr_curve.png')
        plt.close()

if __name__ == "__main__":
    evaluate_model() 