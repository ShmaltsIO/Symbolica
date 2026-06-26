#!/usr/bin/env python3
import os
import argparse
from pathlib import Path

def generate_tree(root_dir, ignore_dirs=('.git', '__pycache__', 'build', 'cmake-build-debug')):
    """
    Рекурсивно обходит root_dir и возвращает список строк для Markdown-дерева.
    """
    lines = []
    root_path = Path(root_dir).resolve()
    # Сортируем папки и файлы для стабильного вывода
    items = sorted(root_path.iterdir(), key=lambda x: (not x.is_dir(), x.name.lower()))
    # Фильтруем игнорируемые папки
    items = [x for x in items if x.name not in ignore_dirs]

    def add_items(path, prefix=''):
        # Получаем отсортированные элементы (папки сверху)
        children = sorted(path.iterdir(), key=lambda x: (not x.is_dir(), x.name.lower()))
        children = [x for x in children if x.name not in ignore_dirs]
        count = len(children)
        for i, child in enumerate(children):
            is_last = (i == count - 1)
            connector = '└── ' if is_last else '├── '
            line = prefix + connector + child.name
            # добавляем маркер для папки
            if child.is_dir():
                line += '/'
            lines.append(line)
            if child.is_dir():
                # следующий префикс: пробелы вместо '│   ' или '    ' в зависимости от последнего
                extension = '    ' if is_last else '│   '
                add_items(child, prefix + extension)

    # Корневой элемент
    lines.append(root_path.name + '/')
    add_items(root_path)
    return lines

def main():
    parser = argparse.ArgumentParser(description='Генерация Markdown-дерева структуры проекта')
    parser.add_argument('--root', default='.', help='Корневая папка (по умолчанию текущая)')
    parser.add_argument('--output', default='structure.md', help='Имя выходного MD-файла')
    parser.add_argument('--ignore', nargs='+', default=['.git', '__pycache__', 'build'],
                        help='Папки для игнорирования')
    args = parser.parse_args()

    lines = generate_tree(args.root, set(args.ignore))
    # Записываем в Markdown-файл
    with open(args.output, 'w', encoding='utf-8') as f:
        # Можно добавить заголовок
        f.write('# Структура проекта\n\n```\n')
        for line in lines:
            f.write(line + '\n')
        f.write('```\n')
    print(f'Дерево сохранено в {args.output}')

if __name__ == '__main__':
    main()