var imageList = []; // Liste pour stocker les noms des images téléchargées

        // Fonction pour afficher les images téléchargées
        function displayImages() {
            var imageListElement = document.getElementById('image-list');
            imageListElement.innerHTML = '';

            // Parcourir la liste des images et les ajouter à la liste
            imageList.forEach(function(imageName) {
                var listItem = document.createElement('li');
                listItem.innerText = imageName;
                imageListElement.appendChild(listItem);
            });
        }

        // Fonction pour supprimer une image
        function deleteImage(imageName) {
            var xhr = new XMLHttpRequest();
            xhr.open('DELETE', 'http://127.0.0.1/' + imageName, true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState === 4 && (xhr.status == 200 || xhr.status == 204 )) {
                    alert('L\'image a ete supprimee avec succes.');
                    // Supprimer l'élément de conteneur de l'image de la liste des images affichées
                    var imageContainer = document.querySelector('.image-container');
                    if (imageContainer) {
                        imageContainer.parentNode.removeChild(imageContainer);
                    }
                    // Mettre à jour la liste des images après la suppression
                    var index = imageList.indexOf(imageName);
                    if (index > -1) {
                        imageList.splice(index, 1);
                        displayImages();
                    }
                } else if (xhr.readyState === 4 && (xhr.status !== 200 || xhr.status !== 204 )) {
                    alert('Une erreur s\'est produite lors de la suppression de l\'image.');
                }
            };
            xhr.send();
        }
        
        var imageInput = document.getElementById('image-input');

        imageInput.addEventListener('change', function(event) {
            var files = event.target.files;

            // Parcourir les fichiers sélectionnés
            for (var i = 0; i < files.length; i++) {
                var file = files[i];
                var reader = new FileReader();

                reader.onload = function(event) {
                    var imageSrc = event.target.result;
                    var imageName = file.name;

                    // Ajouter le nom de l'image à la liste
                    imageList.push(imageName);

                    // Créer un élément d'image pour l'afficher
                    var imageElement = document.createElement('img');
                    imageElement.className = 'uploaded-image';
                    imageElement.src = imageSrc;
                    imageElement.alt = imageName;

                    // Créer un élément de bouton pour supprimer l'image
                    var deleteButton = document.createElement('button');
                    deleteButton.innerText = 'Supprimer';
                    deleteButton.addEventListener('click', function() {
                        deleteImage(imageName);
                    });

                    // Créer un élément de conteneur pour l'image et le bouton de suppression
                    var imageContainer = document.createElement('div');
                    imageContainer.className = 'image-container';
                    imageContainer.appendChild(imageElement);
                    imageContainer.appendChild(deleteButton);

                    // Ajouter le conteneur d'image à la liste des images
                    var imageListElement = document.getElementById('image-list');
                    imageListElement.appendChild(imageContainer);
                };

                reader.readAsDataURL(file);
            }
        });

        document.getElementById('upload-form').addEventListener('submit', function(event) {
            event.preventDefault();
            var formData = new FormData(this);
            var xhr = new XMLHttpRequest();
            xhr.open('POST', 'http://127.0.0.1/upload', true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState === 4 && (xhr.status !== 200 || xhr.status !== 204 )) {
                    alert('L\'image a ete telechargee avec succes.');
                } else if (xhr.readyState === 4 && (xhr.status !== 200 || xhr.status !== 204 )) {
                    alert('Une erreur s\'est produite lors du telechargement de l\'image.');
                }
            };
            xhr.send(formData);
        });