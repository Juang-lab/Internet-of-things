# Internet-of-things

Proyecto: Estación de Temperatura con TMP36 y LCD
Este proyecto implementa un sistema de monitoreo de temperatura utilizando un sensor TMP36, un Arduino UNO, una pantalla LCD 16x2, un LED y un motor (ventilador).
El sistema mide la temperatura ambiente, la muestra en la pantalla LCD y ejecuta acciones de control según tres validaciones definidas.

⚙️ Componentes utilizados
- Arduino UNO
- Sensor de temperatura TMP36
- Pantalla LCD 16x2 (modo 4 bits)
- Potenciómetro de 10kΩ (para contraste del LCD)
- LED rojo con resistencia de 220Ω
- Motor DC (ventilador) con transistor o módulo relay
- Protoboard y cables de conexión

Descripción del funcionamiento
- Lectura de temperatura
- El sensor TMP36 entrega un voltaje proporcional a la temperatura.
- Se convierte la lectura analógica en grados Celsius.
- Visualización en LCD
- En la primera línea se muestra la temperatura en °C.
- En la segunda línea se muestra el estado del sistema (FRÍO, NORMAL o CALOR).
- Validaciones implementadas


<img width="1057" height="305" alt="image" src="https://github.com/user-attachments/assets/b916b7a8-cb2d-46ba-a163-4ca72604bd7d" />
