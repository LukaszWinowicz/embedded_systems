from flask import Flask, jsonify, request

app = Flask(__name__)

# Przykładowe dane z rozszerzoną strukturą
tensometry_data = [
    {"id": 1, "waga": 21.0, "nr_item": "A1", "opis_itemu": "Produkt A", "waga_itemu": 10.5},
    {"id": 2, "waga": 24.6, "nr_item": "B2", "opis_itemu": "Produkt B", "waga_itemu": 12.3},
    # Dodaj więcej danych zgodnie z potrzebami
]

@app.route('/tensometry', methods=['GET'])
def get_tensometry_data():
    # Modyfikujemy dane, dodając 'liczba_sztuk'
    modified_data = []
    for item in tensometry_data:
        liczba_sztuk = item["waga"] / item["waga_itemu"]
        modified_item = item.copy()  # Kopiujemy oryginalny słownik
        modified_item["liczba_sztuk"] = liczba_sztuk
        modified_data.append(modified_item)
    
    return jsonify(modified_data)

if __name__ == '__main__':
    app.run(debug=True)
