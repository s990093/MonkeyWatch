# 定義資料集路徑
DATASET_PATH = /Users/hungwei/Desktop/Proj/Monkey/dataset/data.yaml

.PHONY: train evaluate all

# 默認變數
DATA_PATH = dataset/data.yaml
MODEL_TYPE = yolov8n.pt

# 使用 nano 模型訓練 (預設)
train:
	python src/train.py --data $(DATA_PATH) --model $(MODEL_TYPE)

# 預測影片
predict-video:
	python src/predict.py --source data/video.mp4

# 使用網路攝影機
predict-webcam:
	python src/predict.py --source 0

# 清理訓練產生的檔案
clean:
	rm -rf runs/*

# 評估模型
evaluate:
	python src/evaluate.py --data $(DATA_PATH)

# 訓練並評估模型
all: train evaluate