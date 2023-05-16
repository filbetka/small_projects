import os

from invoke import task


def venv_run(c, command: str):
    c.run('source venv/bin/activate && ' + command)


@task
def start(c):
    if not os.path.exists('venv'):
        c.run('sudo apt-get install -y python3.9-venv')
        c.run('python3.9 -m venv venv')
        venv_run(c, 'pip install pip-tools')
        venv_run(c, 'pip-sync')


@task
def run(c):
    venv_run(c, 'python manage.py runserver')


@task
def db(c):
    venv_run(c, 'python manage.py makemigrations')
    venv_run(c, 'python manage.py migrate')


@task
def precommit(c):
    venv_run(c, 'pre-commit run --all-files')
