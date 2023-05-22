# TER

# Les librairies à installer pour faire fonctionner l'application :

  -PCL version expérimentale;
  
  -OpenCV pour Pyhton;
  
  -VTK qui est une dépendance pour PCL mais aussi pour un code Viewer;
  
  -Boost qui est une dépendance pour PCL;
  
  -Eigen qui est une dépendance pour PCL;
  
  -FLANN qui est une dépendance pour PCL;
  
# Les IDE à installer :

  -QtCreator pour afficher l'application ou possibilité de lancer l'application grâce à un qmake;
  
  -VSCode pour visualiser le code;

# Les builds :

  -Il sera nécessaire de build la librairie PCL;
  
  -Un build sera automatiquement généré lors de la compilation de l'application Qt;
  
  -Il sera nécessaire de build les programmes externes appelés par l'application;
  
# Comment build ?

  -Pour la librairie PCL, lors de l'installation, un fichier CMakeLists.txt sera déjà disponible. Pour build il suffit dans le       dossier de la librairie, d'ajouter un dossier build (mkdir build), d'aller dans ce dossier (cd build), puis de faire : 
  
  cmake ..
  
  puis 
  
  make
  
  -Pour les programmes externes à l'application, il y aura déjà un CMakeLists.txt de disponible lors du clonage du projet. Ainsi     il suffit de répéter les mêmes étapes que pour la librairie PCL, mais cette fois dans le dossier ou se trouvent les programmes     en question (normalement cela correspond au dossier qui englobe tout). Cela va générer des executables dans le build en question   pour chacun des programmes nécessaires.
  
# Paramètres à changer pour faire fonctionner l'application sur VOTRE PC :

   -Dans le dossier intitulé "ter", allez dans le fichier "process.cpp" et changez tous les chemins d'accès aux executables           programmes externes appelés par l'application avec vos propres chemins vers ces exécutables (qui sont présents dans le build).
  
    Exemple : "/home/marie/.../build/cloud_viewer" vous le remplacer par "/home/nom/.../Dossier_clonné/build/cloud_viewer"

  
  
