import os
import webbrowser


def generate_html(n):
    gradient_step = float(255 / n)
    html = ['<table style = "width: 8000px;">']

    for i in range(n):
        color = int(255 - i * gradient_step)
        html.append(
            f'<tr style="padding-bottom: 0px; background-color: rgb({color}, {color}, {color})"><td>{i+1}</td></tr>'
        )

    html.append("</table>")
    return "\n".join(html)


def main():
    n = 155
    filename = "gradient.html"
    with open(filename, "w") as f:
        f.write(generate_html(n))

    # Открываем файл в браузере
    absolute_path = os.path.abspath(filename)
    webbrowser.open("file://" + absolute_path)


if __name__ == "__main__":
    main()
