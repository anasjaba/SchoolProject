$(document).ready(function(){
	// Bouton English
	$("#btnEn").click(function(){
		document.getElementById("city").value = document.getElementById("ville").value
		$("#fr").hide();
		$("#en").show();
	});

	// Bouton Francais
	$("#btnFr").click(function(){
		document.getElementById("ville").value = document.getElementById("city").value
		$("#en").hide();
		$("#fr").show();
	});

	// Boutton Recherche
	$("#btnRecherche").click(function(){
		doSearch("ville");
	});

	// Boutton Search
	$("#btnSearch").click(function(){
		doSearch("city");
	});

	// Recherche d'une ville dans la liste
	function doSearch(lang) {
		var ville = document.getElementById(lang).value;
		document.getElementById("info_fr").innerHTML = "Ville sélectionnée : " + ville;
		document.getElementById("info_en").innerHTML = "Selected city : " + ville;
		dropPin(coords[ville].lat, coords[ville].lon);
	};

	// Listes des villes (String et Object)
	var villes = [];
	var coords;

	// Lecture du fichier .json et autocomplete
	$.getJSON( "villes.json", function( data ) {
		coords = data;
		$.each( data, function( key, val ) {
			villes.push( key );
		});

		$('#ville').autocomplete({
			source: villes
		});
	});

	// Options par défaut de la carte
	var mapOptions = {
		zoom: 10,
		center: new google.maps.LatLng(45.5, -73.550003)
	};

	// Carte
	var map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
	var script = document.createElement('script');
	script.type = 'text/javascript';
	script.src = 'https://maps.googleapis.com/maps/api/js?v=3.exp' + '&signed_in=true&callback=initialize';
	document.body.appendChild(script);


	// Affichage d'un marqueur sur la carte
	function dropPin(lat, lon) {
		var myLatlng = new google.maps.LatLng(lat, lon);
		var mapOptions = {
			zoom: 10,
			center: myLatlng
		};
		map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);
		var marker = new google.maps.Marker({
			position: myLatlng,
			map: map,
			title: 'MARKER'
		});
	}

});
