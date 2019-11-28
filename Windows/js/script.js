/*window.onload = function(){
    document.getElementById("submit").onclick = getData;
}
 
function getData(){
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.open('post', 'upload', true);
    xmlhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded')
 
 
	// создать объект для формы
	var formData = new FormData(document.forms.formFile);
 
	// отослать
	xmlhttp.send(formData);
		
 
    xmlhttp.onreadystatechange = function(){
        if (xmlhttp.readyState == 4) {
            if(xmlhttp.status == 200) {
                document.getElementById("answer").innerHTML += xmlhttp.responseText;
            }
        }
    }
	
	
    if(xhr.status != 200)
    {
			alert("No 200");
    }
    else
    {
         document.getElementById("answer").innerHTML += xmlhttp.responseText;
		 alert("OK 200");
    }
    
    return false;
}
$(document).ready(function(){
	$('#formFile').on("submit", function(){
		$.post(
			'/upload', // адрес обработчика
			new FormData(document.forms.formFile), // отправляемые данные          
			
			function(msg) { // получен ответ сервера  
			console.log("GOOD",msg);
				document.getElementById("answer").innerHTML += xmlhttp.responseText;
			}
		);
		return false;
	});
});



$('#formFile').submit(function(e) {
		
	console.log("test success");
	//Получаем параметры
    // создать объект для формы
    var formData = new FormData(this);

    // Отсылаем паметры
       $.ajax({
                type: "POST",
                url: "/action.php",
                data: formData,
                //При удачном завершение запроса - выводим то, что нам вернул PHP
                success: function(html) {
 //предварительно очищаем нужный элемент страницы
                        $("#answer").empty();
//и выводим ответ php скрипта
                        $("#answer").append(html);
                }
        });
		
	e.preventDefault();	
});
*/


$(function(){
		
	
	
	$('input[type="file"]').change(function(){
		addFiles(this.files);
		
		
       /* var value = $("input[type='file']");
        document.getElementById("fileRead").innerHTML += this.value;
		
		
	 var reader = new FileReader();

	  reader.onload = function (e) {
		// Используем URL изображения для заполнения фона
		//dropBox.style.backgroundImage = "url('" + e.target.result + "')";
		
		console.log("loading");
	  };
	  
	  // Начинаем считывать изображение
	  reader.readAsDataURL(value);
		
		*/
		
    });
	
	function addFiles(files) {
	$.each(files, function(i, v) {
		
		// Считаем файл.
			var fr = new FileReader();
			fr.file = v;
			fr.readAsText(v);
			
			fr.onload = function() {
			console.log(fr.result);
			document.getElementById("fileRead").innerHTML = fr.result;
		  };
		  
		  });
			
	};
	
	
	
  $('#formFile').on('submit', function(e){
    e.preventDefault();

	console.log("test success");
	
   // var form = $('#formFile').serialize(); 
   // let formData = new FormData($(form)[1]) // создаем новый экземпляр объекта и передаем ему нашу форму (*)
    $.ajax({
	  type: "POST",
	  url: "/upload",
	  data: new FormData($("#formFile")[0]),
      contentType: false, // важно - убираем форматирование данных по умолчанию
      processData: false, // важно - убираем преобразование строк по умолчанию
      success: function(json){
        if(json){
          // тут что-то делаем с полученным результатом
			document.getElementById("answer").innerHTML = json;
        }
      }
    });
  });

})


