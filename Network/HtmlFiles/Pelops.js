function deleteImage(imageName) {
    var xhr = new XMLHttpRequest();
    xhr.open('DELETE', 'http://127.0.0.1/test.html', true);
    xhr.onreadystatechange = function() {
        if (xhr.readyState === 4 && xhr.status === 200) {
            alert('L\'image a été supprimée avec succès.');
        } else if (xhr.readyState === 4 && xhr.status !== 200) {
            alert('Une erreur s\'est produite lors de la suppression de l\'image.');
        }
    };
    xhr.send(JSON.stringify({ imageName: imageName }));
}

var imageInput = document.getElementById('image-input');
var uploadedImage = document.getElementById('uploaded-image');
var imageList = document.getElementById('image-list');

imageInput.addEventListener('change', function(event) {
    var file = event.target.files[0];
    var reader = new FileReader();

    reader.onload = function(event) {
        var image = document.createElement('img');
        image.classList.add('uploaded-image');
        image.src = event.target.result;
        imageList.appendChild(image);
    };

    reader.readAsDataURL(file);
});

var deleteButtons = document.querySelectorAll('.delete-button');
for (var i = 0; i < deleteButtons.length; i++) {
    deleteButtons[i].addEventListener('click', function(event) {
        var imageName = event.target.dataset.imageName;
        deleteImage(imageName);
    });
}
