import tkinter as tk
from tkinter import filedialog

def open_file():
    file_path = filedialog.askopenfilename(filetypes=[('Text Files', '*.txt'), ('All Files', '*.*')])
    if file_path:
        with open(file_path, 'r') as file:
            content = file.read()
            text_widget.delete('1.0', tk.END)  # Wyczyszczenie istniejącej zawartości
            text_widget.insert(tk.END, content)

app = tk.Tk()
app.title('Otwieranie Plików')

text_widget = tk.Text(app, wrap='word')
text_widget.pack(expand=True, fill='both')

open_button = tk.Button(app, text='Otwórz Plik', command=open_file)
open_button.pack()

app.mainloop()
