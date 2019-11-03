import xml.etree.ElementTree as ET
root = ET.parse('/home/lisek/Dropbox/__Wazne__/Śpiewnik/Łemata').getroot()

order = root.find('order').text.split(',')
order = [el.strip() for el in order]

for el in order:

    text = root.find(el).text
    lines = [line.strip() for line in text.split('\n')]
    text = '\n'.join(lines)

    print(text.strip())
