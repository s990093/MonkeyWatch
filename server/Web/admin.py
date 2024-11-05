from django.contrib import admin
from .models import *
@admin.register(Image)
class ImageAdmin(admin.ModelAdmin):
    list_display = ('id', 'timestamp', 'is_labeled')  # 在列表頁顯示的欄位
    list_filter = ('is_labeled', 'timestamp')  # 提供過濾選項
    search_fields = ('path',)  # 提供搜尋欄位

@admin.register(MonkeyDetectionEvent)
class MonkeyDetectionEventAdmin(admin.ModelAdmin):
    list_display = ('id', 'image', 'timestamp', 'location', 'monkey_count', 'verdict')
    list_filter = ('location', 'timestamp')
    search_fields = ('location',)
    raw_id_fields = ('image',)  # 使用 raw_id_fields 來改善外鍵欄位的顯示方式

@admin.register(SystemLog)
class SystemLogAdmin(admin.ModelAdmin):
    list_display = ('timestamp', 'logType', 'status', 'message')
    list_filter = ('logType', 'status', 'timestamp')
    search_fields = ('message',)

@admin.register(config)
class configAdmin(admin.ModelAdmin):
    #  根據需要自訂 config 模型的顯示方式
    pass

@admin.register(CompletionStatus)
class CompletionStatusAdmin(admin.ModelAdmin):
    list_display = ('time', 'desc')
    search_fields = ('desc',)
    ordering = ('-time',)

@admin.register(Task)
class TaskAdmin(admin.ModelAdmin):
    list_display = ('name', 'time')
    search_fields = ('name',)
    ordering = ('-time',)

@admin.register(DailyTask)
class DailyTaskAdmin(admin.ModelAdmin):
    list_display = ('name', 'task_type', 'completion_status')
    search_fields = ('name',)
    list_filter = ('task_type',)
    ordering = ('-time',)

@admin.register(WeeklyTask)
class WeeklyTaskAdmin(admin.ModelAdmin):
    list_display = ('task', 'day_of_week')
    search_fields = ('task__name',)
    list_filter = ('day_of_week',)
    ordering = ('task', 'day_of_week')

