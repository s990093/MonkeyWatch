import serial
import matplotlib.pyplot as plt
from drawnow import drawnow
import time
from datetime import datetime
from rich.console import Console
import click

# Store received data
data = {'x': [], 'y': []}


# Initialize console for rich output
console = Console()

# Callback function to update plot
def plot_data():
    plt.title('Real-time Data from ESP32')
    plt.xlabel('Time')
    plt.ylabel('Value')
    plt.grid(True)
    plt.plot(data['x'], data['y'], 'ro-', label='Data')
    plt.legend(loc='upper left')

@click.command()
@click.option('--serial-port', default='/dev/tty.usbserial-110', help='Serial port for ESP32 communication')
def main(serial_port):
    baud_rate = 115200
    ser = serial.Serial(serial_port, baud_rate)

    try:
        while True:
            try:
                if ser.in_waiting > 0:
                    line = ser.readline().decode('utf-8').strip()
                    timestamp = datetime.now().strftime('%H:%M:%S')  # Get current timestamp
                    console.print(f'{timestamp} --> {line}')  # Print received data with timestamp

                    parts = line.split(',')
                    if len(parts) == 2:
                        x, y = map(float, parts)  # Convert parts to float values
                        data['x'].append(x)
                        data['y'].append(y)

                        drawnow(plot_data)  # Update plot

            except KeyboardInterrupt:
                raise
            except Exception as e:
                console.print(f'Exception occurred: {e}')
                time.sleep(1)  # Wait before retrying connection

    except KeyboardInterrupt:
        console.print('Stopping data reception')

    finally:
        # Close serial port
        if ser.is_open:
            ser.close()

if __name__ == "__main__":
    main()
