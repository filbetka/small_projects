from invoke import task
import os


def venv_run(c, command: str):
    c.run('source venv/bin/activate && ' + command)


@task
def start(c):
    if not os.path.exists('venv'):
        c.run('sudo apt-get install -y python3.9-venv')
        c.run('python3.9 -m venv venv')
        venv_run(c, 'pip install -r requirements.txt')


@task
def run(c):
    venv_run(c, 'python manage.py runserver')

