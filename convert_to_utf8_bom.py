import os
import subprocess

try:
    import chardet
except ImportError:
    print('chardet is not installed. Installing...')
    subprocess.run(['pip', 'install', 'chardet'])
    import chardet

# 获取当前路径
current_dir = os.getcwd()

# 遍历当前目录及子目录下的所有 .h .cpp 文件
file_list = []
for root, dirs, files in os.walk(current_dir):
    for filename in files:
        if filename.endswith('.h') or filename.endswith('.cpp'):
            filepath = os.path.join(root, filename)
            file_list.append(filepath)

# 打印文件信息
print(f'{"序号":<5} {"文件名":<50} {"原来格式":<20} {"转换后格式":<20} {"是否转换成功":<15}')
success_count = 0
for i, filepath in enumerate(file_list, 1):
    with open(filepath, 'rb') as f:
        # 检测原来的编码格式
        before_encoding = chardet.detect(f.read())['encoding']
    if before_encoding is None:
        before_encoding = 'unknown'
    # 转换编码格式为 UTF-8 BOM
    try:
        with open(filepath, 'r', encoding=before_encoding) as f:
            content = f.read()
        with open(filepath, 'w', encoding='utf-8-sig') as f:
            f.write(content)
        success = True
        success_count += 1
    except:
        success = False
    # 检测转换后的编码格式
    with open(filepath, 'rb') as f:
        after_encoding = chardet.detect(f.read())['encoding']
    if after_encoding is None:
        after_encoding = 'unknown'
    # 打印文件信息
    print(f'{i:<5} {filepath:<50} {before_encoding:<20} {after_encoding:<20} {"Yes" if success else "No":<15}')
print(f'Total: {len(file_list)}, success: {success_count}, failed: {len(file_list)-success_count}')
