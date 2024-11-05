import torch
from ultralytics import YOLO
import click
import os
import logging

from helper.show_parameters import show_parameters

# Set up logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

@click.command()
@click.option('--data', 
              default='/Users/hungwei/Desktop/Proj/Monkey/dataset/data.yaml',
              help='Path to the dataset configuration file')
@click.option('--model',
              default='yolov8n.pt',
              help='Model type (yolov8n.pt, yolov8s.pt, yolov8m.pt, yolov8l.pt, yolov8x.pt)')
@click.option('--epochs', default=100, help='Number of training epochs', type=int)
@click.option('--imgsz', default=640, help='Image size', type=int)
@click.option('--batch-size', default=16, help='Batch size', type=int)
@click.option('--device', 
              default=None, 
              help='Device to use ("mps" for Apple Silicon GPU, "cuda" for NVIDIA GPU, "cpu" for CPU)')
def train_model(data, model, epochs, imgsz, batch_size, device):
    # Validate inputs
    if not os.path.isfile(data):
        logging.error(f"Dataset configuration file does not exist: {data}")
        return

    if not os.path.isfile(model):
        logging.error(f"Model file does not exist: {model}")
        return

    # Auto-detect device if not specified
    if device is None:
        if torch.cuda.is_available():
            device = 'cuda'
        elif torch.backends.mps.is_available():
            device = 'mps'
        else:
            device = 'cpu'
        logging.info(f"Automatically selected device: {device}")
    
    # Initialize YOLO model
    yolo_model = YOLO(model)
    
    # Show parameters
    show_parameters(data, model, epochs, imgsz, batch_size, device)

    # Train model
    try:
        logging.info("Starting training...")
        yolo_model.train(
            data=data, 
            epochs=epochs,
            batch=batch_size,
            imgsz=imgsz,
            device=device
        )
        logging.info("Training completed successfully.")
    except Exception as e:
        logging.error(f"An error occurred during training: {e}")

if __name__ == "__main__":
    train_model()
