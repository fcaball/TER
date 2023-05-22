# Reconstruction 3D d'objets à partir d'images 2D, par la photogrammétrie - La Fratrie des lumières

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

  -Pour la librairie PCL, lors de l'installation, un fichier CMakeLists.txt sera déjà disponible. Pour build il suffit, dans le      dossier de la librairie, vous devrait faire les lignes de commandes suivantes : 
  
  ```bash
  mkdir build
  cd build
  cmake ..
  make
  ```
 
  
  -Pour les programmes externes à l'application, il y aura déjà un CMakeLists.txt, dans le dossier "application_photogrammétrie", de disponible lors du clonage du projet. Vous devez appeler le dossier par : "buildPCL". Donc il faudra faire les lignes de commandes suivantes :
  
  ```bash
  mkdir buildPCL
  cd buildPCL
  cmake ..
  make
  ```
  
  Cela génèrera les exécutables nécessaire à la bonne exécution des options de l'application.
 
  
    
  
  
