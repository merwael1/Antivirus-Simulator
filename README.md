# 🛡️ Toy Antivirus – Notre projet étudiant

## 👥 Contributeurs
- YASSINE  | Étape 1️⃣ : Structures et prototypes
- MERWA    | Étape 2️⃣ : Gestion des fichiers
- ADAM     | Étape 3️⃣ : Gestion des signatures
- MALAK    | Étape 4️⃣ : Scan
- HAMZA    | Étape 5️⃣ : Nettoyage



---

## 📝 À propos du projet

Nous créerons un simulateur antivirus en C pour apprendre à manipuler des fichiers et des signatures avec des listes chaînées.  

💡 Ce projet ne contiendra aucun vrai virus, il servira uniquement à comprendre comment un antivirus fonctionnera :  

- Nous gérerons des fichiers et des signatures  
- Nous implémenterons un scan simple basé sur des patterns  
- Nous déplacerons des fichiers entre listes (Clean, Suspect, Quarantine)  
- Nous créerons une interface CLI pour interagir avec le programme  
- Nous gérerons manuellement la mémoire (`malloc` / `free`)  

---

## 🕒 Chronologie du développement

Voici comment nous construirons notre projet, étape par étape :  

### Étape 1️⃣ : Structures et prototypes

**Fichiers :** `filelist.h` + `siglist.h`  

Nous commencerons par définir `FileRec` et `Sig`, ainsi que toutes les fonctions principales que nous utiliserons ensuite.  

🎯 **Objectif :** poser les fondations pour tout le projet.

---

### Étape 2️⃣ : Gestion des fichiers

**Fichier :** `filelist.c`  

Nous coderons :  

- Création de fichiers (`create_file`)  
- Ajout dans une liste (`insert_file`)  
- Suppression ou recherche (`remove_file`, `find_file`)  
- Déplacement entre listes (`move_file`)  
- Affichage et libération mémoire (`print_list`, `free_list`)  

✅ Nous testerons chaque fonction avec un petit `main` temporaire pour vérifier que les pointeurs fonctionneront correctement.

---

### Étape 3️⃣ : Gestion des signatures

**Fichier :** `siglist.c`  

Nous coderons :  

- Création de signatures (`create_sig`)  
- Ajout / suppression (`insert_sig`, `delete_sig`)  
- Affichage et libération mémoire (`print_sigs`, `free_sigs`)  

Nous vérifierons que l’ajout et la suppression fonctionneront avant de coder le scan.

---

### Étape 4️⃣ : Scan

**Fichier :** `scan.c`  

Nous coderons :  

- Parcours de la liste Clean  
- Comparaison avec toutes les signatures (`strstr`)  
- Déplacement des fichiers suspects vers Suspect  
- Mise à jour du flag `suspicious = 1`  

⚠️ Nous gérerons correctement les pointeurs pour ne pas casser la liste.

---

### Étape 5️⃣ : Nettoyage

**Fichier :** `cleanup.c`  

Nous coderons `purge_all()` pour :  

- Libérer toutes les listes : Clean, Suspect, Quarantine, Signatures  
- Mettre tous les pointeurs à NULL pour éviter les fuites mémoire  

🧹 Cette étape nous permettra de vérifier que la gestion de la mémoire sera correcte.

---

### Étape 6️⃣ : Interface CLI

**Fichier :** `main.c`  

Nous coderons la boucle principale et les commandes :  

- `ADD_SIG` / `DEL_SIG`  
- `LOAD`  
- `SCAN`  
- `QUAR` / `RESTORE`  
- `REPORT`  
- `PURGE` / `EXIT`  

🖥️ Nous commencerons par tester les commandes simples (`ADD_SIG`, `LOAD`, `REPORT`) puis nous intégrerons `SCAN` et `QUAR`.

---

