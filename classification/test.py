from ultralytics import YOLO
import cv2
import torch
import click
import platform

# 設置設備選擇
if platform.system() == 'Darwin':  # macOS
    device = torch.device("mps" if torch.backends.mps.is_available() else "cpu")
elif platform.system() == 'Windows' or platform.system() == 'Linux':
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
else:
    device = torch.device("cpu")
print(f"Using device: {device}")

@click.command()
@click.option('--path', required=True, help='Path to the monkey detection model weights')
def run_detection(path):
    # 加載猴子辨識模型並指定設備
    monkey_model = YOLO(path).to(device)

    # 打開影片
    cap = cv2.VideoCapture("data/test.mp4")

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret:
            break

        # 使用模型進行猴子檢測
        results = monkey_model(frame)
        annotated_frame = frame.copy()

        # 如果檢測到猴子
        if len(results[0].boxes) > 0:
            for box in results[0].boxes:
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                conf = float(box.conf)
                cls = int(box.cls)
                cls_name = results[0].names[cls]
                
                # 繪製檢測結果（綠色框）
                cv2.rectangle(annotated_frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                label = f'{cls_name} {conf:.2f}'
                cv2.putText(annotated_frame, label, (x1, y1 - 10), 
                           cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

        # 顯示結果
        cv2.imshow("Monkey Detection Model", annotated_frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # 釋放資源
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    run_detection()
