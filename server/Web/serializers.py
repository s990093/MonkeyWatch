from collections import defaultdict
from rest_framework import serializers
from .models import WeeklyTask, DailyTask, CompletionStatus


class CompletionStatusSerializer(serializers.ModelSerializer):
    class Meta:
        model = CompletionStatus
        fields = ['time', 'desc']


class DailyTaskSerializer(serializers.ModelSerializer):
    completion_status = CompletionStatusSerializer()

    class Meta:
        model = DailyTask
        fields = ['name', 'task_type', 'completion_status']


class WeeklyTaskSerializer(serializers.ModelSerializer):
    task = DailyTaskSerializer()

    class Meta:
        model = WeeklyTask
        fields = ['id', 'task', 'day_of_week']


class GroupedWeeklyTaskSerializer(serializers.Serializer):
    """
    Serializer that groups tasks by days of the week.
    """

    def to_representation(self, instance):
        grouped_tasks = defaultdict(list)

        # Group tasks by 'day_of_week'
        for weekly_task in instance:
            serialized_task = {
                'id': weekly_task.id,
                'task': DailyTaskSerializer(weekly_task.task).data
            }
            grouped_tasks[weekly_task.day_of_week].append(serialized_task)

        return grouped_tasks