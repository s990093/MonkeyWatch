from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from rest_framework.generics import ListAPIView, UpdateAPIView
from .models import *
from .serializers import GroupedWeeklyTaskSerializer, WeeklyTaskSerializer, CompletionStatusSerializer
from django.shortcuts import get_object_or_404
import json


def monkeyEventShow(request):
    if(request.GET.get("date") == None) :
        events= MonkeyDetectionEvent.objects.all()
        event_list = []
        for event in events:
            event_data = {
                'id': event.id,
                'image_id': event.image.id,  # Include the related image ID
                'timestamp': event.timestamp.isoformat(),  # Format timestamp for JSON serialization
                'location': event.location,
                'monkey_count': event.monkey_count,
                'verdict': event.verdict,
                'mark': event.mark,
            }
        event_list.append(event_data)
        return json.dumps(event_list)
    else :
        pass
# List all WeeklyTasks
class WeeklyTaskView(APIView):
    def get(self, request):
        # Get all weekly tasks
        weekly_tasks = WeeklyTask.objects.all()

        # Pass queryset to the serializer
        serializer = GroupedWeeklyTaskSerializer(weekly_tasks)

        # Return serialized data
        return Response(serializer.data)
    
# Patch API to update task completion status
class TaskCompletionUpdateView(UpdateAPIView):
    serializer_class = CompletionStatusSerializer

    def patch(self, request, pk, *args, **kwargs):
        task = get_object_or_404(DailyTask, pk=pk)
        completion_status_data = request.data.get('completion_status')

        # Either create a new CompletionStatus or update the existing one
        if task.completion_status:
            completion_status = task.completion_status
            serializer = CompletionStatusSerializer(completion_status, data=completion_status_data, partial=True)
        else:
            serializer = CompletionStatusSerializer(data=completion_status_data)

        if serializer.is_valid():
            # If no existing completion status, assign the newly created one
            if not task.completion_status:
                completion_status = serializer.save()
                task.completion_status = completion_status
                task.save()
            else:
                serializer.save()
            return Response(serializer.data, status=status.HTTP_200_OK)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
