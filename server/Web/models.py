from django.db import models
from django.utils import timezone

class Image(models.Model):
    image = models.ImageField(upload_to='images/') 
    detection_results = models.JSONField(default=dict)  # 儲存檢測結果，例如：{'monkey_count': 2, 'location': [100, 200]}
    timestamp = models.DateTimeField(auto_now_add=True)  # 自動記錄圖片上傳時間
    is_labeled = models.BooleanField(default=False)     # 是否已標記


    def __str__(self):
        return f"Image {self.id} - {self.timestamp}"



class MonkeyDetectionEvent(models.Model):
    image = models.ForeignKey(Image, on_delete=models.CASCADE, related_name='events')  # 與 Image 模型建立關聯
    timestamp = models.DateTimeField(auto_now_add=True)
    location = models.CharField(max_length=255)  #  例如： "區域 A" 或經緯度座標
    monkey_count = models.PositiveIntegerField(default=0)
    verdict =models.IntegerField(default=0)
    mark =models.JSONField(default=dict)
    # ... 其他需要的欄位，例如：事件的置信度等 ...

    def __str__(self):
        return f"Event {self.id} - {self.timestamp}"

class SystemLog(models.Model):
    timestamp = models.DateTimeField(auto_now_add=True)
    logType = models.IntegerField()
    status = models.IntegerField()
    message = models.TextField()
    metadata = models.JSONField(default=dict)

    def __str__(self):
        return f"{self.timestamp} - Type: {self.logType}, Status: {self.status}, Message: {self.message}"

class config (models.Model):
    notificationWay =models.JSONField(default=dict)


class CompletionStatus(models.Model):
    time = models.DateTimeField(
        default=timezone.now,
        verbose_name="Completion Time"
    )
    desc = models.TextField(
        blank=True,
        verbose_name="Completion Description"
    )

    def __str__(self):
        return f"Completed at {self.time}"



class Task(models.Model):
    name = models.CharField(
        max_length=100, 
        verbose_name="Task Name"
    )
    time = models.DateTimeField(
        verbose_name="Scheduled Time", 
        auto_now_add=True
    )

    def __str__(self):
        return self.name

class DailyTask(Task):
    TASK_TYPE_CHOICES = [
        ('Work', 'Work'),
        ('Language', 'Language'),
        ('Study', 'Study'),
    ]
    
    task_type = models.CharField(
        max_length=50, 
        choices=TASK_TYPE_CHOICES, 
        verbose_name="Task Type" 
    )
    completion_status = models.OneToOneField(
        CompletionStatus, 
        on_delete=models.SET_NULL, 
        null=True, 
        blank=True, 
        verbose_name="Completion Status"
    )

    def __str__(self):
        return f'{self.name} - {self.task_type}'


class WeeklyTask(models.Model):
    DAYS_OF_WEEK = [
        ('Monday', 'Monday'),
        ('Tuesday', 'Tuesday'),
        ('Wednesday', 'Wednesday'),
        ('Thursday', 'Thursday'),
        ('Friday', 'Friday'),
        ('Saturday', 'Saturday'),
        ('Sunday', 'Sunday'),
    ]

    task = models.ForeignKey(DailyTask, on_delete=models.CASCADE, verbose_name="Task")
   
    day_of_week = models.CharField(
        max_length=9, 
        choices=DAYS_OF_WEEK, 
        verbose_name="Day of Week"
    )

    def __str__(self):
        return f'{self.task.name} on {self.day_of_week}'


