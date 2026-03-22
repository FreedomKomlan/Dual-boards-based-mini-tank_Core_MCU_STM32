#!/bin/bash

# Message de commit par défaut avec la date
COMMIT_MESSAGE="Commit on $(date '+%Y-%m-%d %H:%M'): First build with STM32Cube to test the setup and led blinking."

# Aller dans le dossier du projet (à adapter)
cd "C:\Users\kfree\Documents\Data_Elcool\Projets\Software Dev\SY-3_STMX" || exit

# Ajouter tous les fichiers modifiés
git add .

# Faire le commit
git commit -m "$COMMIT_MESSAGE"

# Pousser sur la branche principale (à adapter si tu utilises une autre branche)
git push origin main