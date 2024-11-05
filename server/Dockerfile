# 使用 Python 3.12 的基礎映像檔
FROM python:3.12

# 設定工作目錄
WORKDIR /app

# 將目前目錄的所有檔案複製到容器的工作目錄
COPY . .

# 安裝 requirements.txt 中列出的套件
RUN pip install -r requirements.txt
EXPOSE 8000

# 執行 Django manage.py
CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]