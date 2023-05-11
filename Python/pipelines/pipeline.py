lines = (line for line in open('input'))
tasks = (next(lines) for line in lines if '@task' in line)
task_names = (task.split()[1].split('(')[0] for task in tasks)
for name in task_names:
    print(name)

