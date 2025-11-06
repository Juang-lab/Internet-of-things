# Script: Get Data (Temp and Hum) from Arduino and send to Supabase
import serial
import time
from supabase import create_client, Client
from getPort import port

# Supabase Config
url = "https://uxkrenpypsvnbzozvngy.supabase.co"
key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6InV4a3JlbnB5cHN2bmJ6b3p2bmd5Iiwicm9sZSI6ImFub24iLCJpYXQiOjE3NjE4NTkwNDcsImV4cCI6MjA3NzQzNTA0N30.y0Oof50pOn-fv8qHlKgYb52bTj5W0izCzmsf8PV16gw"

supabase: Client = create_client(url, key)

# Arduino Serial Config
arduino_port = port
baud_rate = 9600
ser = serial.Serial(arduino_port, baud_rate, timeout=1)

time.sleep(2)

print("✅ Conectado al Arduino en", arduino_port)
print("📡 Enviando datos a Supabase cada 1s...\n")

while True:
    data = ser.readline().decode('utf-8').strip()

    if data:
        try:
            humedad, temperatura = data.split(",")
            humedad = float(humedad)
            temperatura = float(temperatura)

            # --- ENVÍO A SUPABASE ---
            response = supabase.table("datos").insert({
                "humedad": humedad,
                "temperatura": temperatura
            }).execute()

            print(f"✅ Enviado | Hum: {humedad}% Temp: {temperatura}°C")

        except ValueError:
            print("⚠️ Formato inválido. Se esperaba: humedad,temperatura | Recibido:", data)

        except Exception as e:
            print("❌ Error al enviar a Supabase:", e)

    time.sleep(1)
