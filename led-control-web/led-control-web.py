from http.server import BaseHTTPRequestHandler, HTTPServer
import serial

# Połącz się z Arduino (podmień port na swój)
arduino = serial.Serial('COM5', 19200)

# Prosta strona HTML z przyciskami
html_page = b"""
<!DOCTYPE html>
<html>
<head><title>Sterowanie Arduino</title></head>
<body>
<h1>Steruj LED</h1>
<button onclick="fetch('/on')">Wlacz LED</button>
<button onclick="fetch('/off')">Wylacz LED</button>
</body>
</html>
"""
class RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            # Wyświetl stronę HTML
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(html_page)

        elif self.path == '/on':
            arduino.write(b'1')  # Włącz LED
            self.send_response(200)
            self.end_headers()
            self.wfile.write(b'LED wlaczony')

        elif self.path == '/off':
            arduino.write(b'0')  # Wyłącz LED
            self.send_response(200)
            self.end_headers()
            self.wfile.write(b'LED wylaczony')

        else:
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b'Nie znaleziono')

if __name__ == '__main__':
    ip = '192.168.34.4'
    port = 8000
    print(f'Serwer działa na http://{ip}:{port}')
    server = HTTPServer((ip, port), RequestHandler)
    server.serve_forever()
