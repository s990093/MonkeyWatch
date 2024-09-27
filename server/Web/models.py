from django.db import models
from django.utils import timezone


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


