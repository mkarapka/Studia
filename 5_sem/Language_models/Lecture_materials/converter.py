import nbformat
import json


def convert_json_to_ipynb(read_file_json, write_file_ipynb):
    def load_json(file):
        with open(file, "r", encoding="utf-8") as read_file:
            return json.load(read_file)

    # Wczytaj dane JSON
    json_data = load_json(read_file_json)
    nb = nbformat.v4.new_notebook()

    for item in json_data.get("cells", []):
        cell_type = item.get("cell_type", "")
        source = item.get("source", "")

        if cell_type == "code":
            new_cell = nbformat.v4.new_code_cell(source)
            outputs = item.get("outputs", [])
            for output in outputs:
                if output.get("output_type") == "stream":
                    new_cell.outputs.append(
                        nbformat.v4.new_output(
                            output_type="stream",
                            name=output.get("name", "stdout"),
                            text=output.get("text", ""),
                        )
                    )
            nb.cells.append(new_cell)
        elif cell_type == "markdown":
            nb.cells.append(nbformat.v4.new_markdown_cell(source))

    # Zapisz notebook do pliku
    with open(write_file_ipynb, "w", encoding="utf-8") as write_file:
        nbformat.write(nb, write_file)


# while True:
#     text_json = input("Pass name of json file: ")
#     text_ipynb = input("Pass name of ipynb file or skip by enter to set default name: ")
#     print(text_ipynb)

#     if text_ipynb == "":
#         text_ipynb = text_json.replace("json", "ipynb")
#     try:
#         covert_json_to_ipynb(text_json, text_ipynb)
#     except:
#         pass
#         break
input_file = r"C:\Users\mikol\Desktop\Studia\5_sem\Language_models\Lecture_materials\word2vec.json"
output_file = r"C:\Users\mikol\Desktop\Studia\5_sem\Language_models\Lecture_materials\word2vec_converted.ipynb"

# Konwersja
convert_json_to_ipynb(input_file, output_file)
