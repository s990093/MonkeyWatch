# MonkeyWatch

此系統旨在使用 CAM AMB82 攝影機監控猴子入侵學校區域。捕獲的影像將通過 ESP32 傳送至後端的 Django 伺服器。後端將負責使用 YOLO 模型對影像進行訓練和偵測，並將識別結果透過 Next.js 顯示在前端。

## 系統架構

### 1. 總覽

本系統旨在監控猴子入侵學校區域，捕獲的影像將通過 ESP32 傳送至後端的 Django 伺服器。後端將負責使用 YOLO 模型進行影像的訓練和偵測，並透過 Next.js 顯示識別結果。

### 2. 技術棧

- **硬體**: CAM AMB82 攝影機, ESP32
- **前端**: Next.js
- **後端**: Django
- **圖像分析**: YOLO (You Only Look Once) 物件偵測
- **網路協定**: MQTT 或 WebSocket
- **資料庫**: PostgreSQL 或 MySQL（用於儲存偵測結果）

## 硬體設定

### 1. CAM AMB82 攝影機

使用 CAM AMB82 處理圖像資料並通過 MQTT 或 WebSocket 將資料傳送至 Django 後端伺服器。以下是設定步驟：

1. **安裝並配置攝影機固件**:

   - 確保攝影機固件為最新版本，以便於更穩定的影像傳輸。
   - 在攝影機的管理界面中，設定網絡參數（如 Wi-Fi 名稱和密碼）。

2. **配置影像傳輸**:

   - 設定影像的分辨率和幀率，以適應後端處理能力。
   - 選擇傳輸協定：可以選擇使用 MQTT 以節省帶寬，或使用 WebSocket 以獲得更快的反應時間。

3. **測試影像捕捉與傳送**:
   - 使用內建的測試功能確認攝影機是否能成功捕獲並傳送影像。
   - 檢查 ESP32 是否能正確接收和轉發影像至 Django 伺服器。

## Django 後端設置

1. **環境搭建**:

   - 使用虛擬環境（如 `venv` 或 `conda`）來隔離項目依賴。
   - 都用.env
   - 用者個安裝:

   ```bash
   python install.py
   ```

2. **創建 Django 專案**:

   - 使用 Django 命令行工具創建新的專案和應用：
     ```bash
     django-admin startproject monkey_monitoring
     cd monkey_monitoring
     django-admin startapp detection
     ```

3. **整合 YOLO 模型**:
   - 將 YOLO 模型整合進 Django 應用，使用如 OpenCV 等庫進行影像處理和物件偵測。
   - 自定義猴子訓練 set
   - 設置 API 接口以接收 ESP32 傳送的影像資料並返回偵測結果。

## 前端顯示

### 1. Next.js 前端設置

1. **創建 Next.js 專案**:

   - 使 yarn 為主

2. **設置 API 請求**:

   - 使用 Axios 從 Django 後端獲取偵測結果並在前端進行顯示。

3. **顯示結果**:
   - 利用 Next.js 的組件架構，設計用於顯示偵測結果的頁面。
