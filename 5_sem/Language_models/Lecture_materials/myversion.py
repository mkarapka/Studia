import nbformat
import json


def covert_json_to_ipynb(read_file_json, write_file_ipynb):
    def load_json(file):
        with open(file, "r", encoding="utf-8") as read_file:
            return json.load(read_file)

    json_data = load_json(read_file_json)
    nb = nbformat.v4.new_notebook()

    for item in json_data["cells"]:
        if item["cell_type"] == "code":
            nb.cells.append(nbformat.v4.new_code_cell(item["source"]))
        else:
            nb.cells.append(nbformat.v4.new_markdown_cell(item["source"]))

    with open(write_file_ipynb, "w", encoding="utf-8") as write_file:
        nbformat.write(nb, write_file)


while True:
    text_json = input("Pass name of json file: ")
    text_ipynb = input("Pass name of ipynb file or skip by enter to set default name: ")
    try:
        if text_ipynb == "":
            text_ipynb = text_json.replace("json", "ipynb")
        covert_json_to_ipynb(text_json, text_ipynb)
        break
    except:
        print("Wrong name of json file!!!")
