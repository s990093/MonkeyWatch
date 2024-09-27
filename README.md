# MonkeyWatch
此系統旨在使用 CAM AMB82 攝影機監控猴子入侵學校區域。捕獲的影像將通過 ESP32 傳送至後端的 Django 伺服器。後端將負責使用 YOLO 模型對影像進行訓練和偵測，並將識別結果透過 Next.js 顯示在前端。
