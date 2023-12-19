# Minishell - Projet 42 🚀

## Description
Minishell est un projet réalisé dans le cadre du cursus de l'école 42. Il s'agit d'implémenter un shell minimaliste en langage C, capable d'exécuter des commandes simples, de gérer les erreurs et de fournir une expérience utilisateur basique.

## Fonctionnalités
- Interprétation et exécution de commandes simples
- Gestion des erreurs utilisateur et système
- Gestion des signaux
- Redirections simples (<, >, >>)
- Pipes pour l'exécution de commandes en série

## Installation
1. Clonez le repository : `git clone https://github.com/CafeurOff/Minishell.git`
2. Naviguez vers le répertoire du projet : `cd minishell`
3. Compilez le projet : `make`

## Utilisation
1. Exécutez le shell : `./minishell`
2. Entrez des commandes simples, utilisez les redirections ou les pipes.
3. Pour quitter le shell, utilisez la commande `exit` ou `Ctrl + D`.

## Exemples
```bash
$ ./minishell
$ ls -l
$ cd dossier
$ echo "Hello, World!" > fichier.txt
$ cat fichier.txt
$ ls | grep fichier
$ exit
```

## Contributions
Les contributions sont les bienvenues. Si vous souhaitez contribuer au projet, veuillez suivre ces étapes :
1. Fork du projet
2. Création d'une nouvelle branche : `git checkout -b feature/nouvelle_fonctionnalite`
3. Commit de vos modifications : `git commit -m "Ajout d'une nouvelle fonctionnalité"`
4. Push vers la branche : `git push origin feature/nouvelle_fonctionnalite`
5. Ouvrir une Pull Request

## Mon travail et celui de mon partenaire 😎

#lduthill :
- `cd`
- `echo`
- `export`
- `unset`
- `env`
- `Gestion des signaux`

#roroca :
- `Parsing`
- `Redirections`
- `exit`

Les deux :
- `Pipes`
