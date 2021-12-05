(function() {
  loadOptions();
  submitHandler();
})();

function submitHandler() {
  var $submitButton = $('#submitButton');

  $submitButton.on('click', function() {
    console.log('Submit');

    document.location = 'pebblejs://close#' + encodeURIComponent(JSON.stringify(getAndStoreConfigData()));
  });
}

function loadOptions() {
  var $unit = document.getElementsByName("unit-tab");
  var $lbs = $('#lbs');
  var $kgs = $('#kgs');
  var $barbellWeight = $('#barbell-weight');
  var $weight100lbs = $('#weight-100-lbs');
  var $weight55lbs = $('#weight-55-lbs');
  var $weight45lbs = $('#weight-45-lbs');
  var $weight35lbs = $('#weight-35-lbs');
  var $weight25lbs = $('#weight-25-lbs');
  var $weight10lbs = $('#weight-10-lbs');
  var $weight5lbs = $('#weight-5-lbs');
  var $weight2point5lbs = $('#weight-2point5-lbs');
  var $weight50kgs = $('#weight-50-kgs');
  var $weight25kgs = $('#weight-25-kgs');
  var $weight20kgs = $('#weight-20-kgs');
  var $weight15kgs = $('#weight-15-kgs');
  var $weight10kgs = $('#weight-10-kgs');
  var $weight5kgs = $('#weight-5-kgs');
  var $weight2point5kgs = $('#weight-2point5-kgs');
  var $weight1point25kgs = $('#weight-1point25-kgs');

  if (!isNaN(localStorage.unitSystem)) {
    $unit[localStorage.unitSystem].className = "tab-button active";
    $unit[1-localStorage.unitSystem].className = "tab-button";
    if (localStorage.unitSystem == 0)
    {
      $lbs.style.display = "block";
      $kgs.style.display = "none";
    }
    else if (localStorage.unitSystem == 1)
    {
      $lbs.style.display = "none";
      $kgs.style.display = "block";
    }
    $barbellWeight[0].value = localStorage.barWeight;
    $weight100lbs[0].value = localStorage.w100p;
    $weight55lbs[0].value = localStorage.w55p;
    $weight45lbs[0].value = localStorage.w45p;
    $weight35lbs[0].value = localStorage.w35p;
    $weight25lbs[0].value = localStorage.w25p;
    $weight10lbs[0].value = localStorage.w10p;
    $weight5lbs[0].value = localStorage.w5p;
    $weight2point5lbs[0].value = localStorage.w2point5p;
    $weight50kgs[0].value = localStorage.w50k;
    $weight25kgs[0].value = localStorage.w25k;
    $weight20kgs[0].value = localStorage.w20k;
    $weight15kgs[0].value = localStorage.w15k;
    $weight10kgs[0].value = localStorage.w10k;
    $weight5kgs[0].value = localStorage.w5k;
    $weight2point5kgs[0].value = localStorage.w2point5k;
    $weight1point25kgs[0].value = localStorage.w1point25k;
  }
}

function getAndStoreConfigData() {
  var $unit = document.getElementsByName("unit-tab");
  var $barbellWeight = $('#barbell-weight');
  var $weight100lbs = $('#weight-100-lbs');
  var $weight55lbs = $('#weight-55-lbs');
  var $weight45lbs = $('#weight-45-lbs');
  var $weight35lbs = $('#weight-35-lbs');
  var $weight25lbs = $('#weight-25-lbs');
  var $weight10lbs = $('#weight-10-lbs');
  var $weight5lbs = $('#weight-5-lbs');
  var $weight2point5lbs = $('#weight-2point5-lbs');
  var $weight50kgs = $('#weight-50-kgs');
  var $weight25kgs = $('#weight-25-kgs');
  var $weight20kgs = $('#weight-20-kgs');
  var $weight15kgs = $('#weight-15-kgs');
  var $weight10kgs = $('#weight-10-kgs');
  var $weight5kgs = $('#weight-5-kgs');
  var $weight2point5kgs = $('#weight-2point5-kgs');
  var $weight1point25kgs = $('#weight-1point25-kgs');

  var options = {
    unitSystem: parseFloat(getUnitSystem()),
    barWeight: parseFloat(getBarbellWeight(getUnitSystem(), $barbellWeight.val())),
    w100p: parseFloat($weight100lbs.val()),
    w55p: parseFloat($weight55lbs.val()),
    w45p: parseFloat($weight45lbs.val()),
    w35p: parseFloat($weight35lbs.val()),
    w25p: parseFloat($weight25lbs.val()),
    w10p: parseFloat($weight10lbs.val()),
    w5p: parseFloat($weight5lbs.val()),
    w2point5p: parseFloat($weight2point5lbs.val()),
    w50k: parseFloat($weight50kgs.val()),
    w25k: parseFloat($weight25kgs.val()),
    w20k: parseFloat($weight20kgs.val()),
    w15k: parseFloat($weight15kgs.val()),
    w10k: parseFloat($weight10kgs.val()),
    w5k: parseFloat($weight5kgs.val()),
    w2point5k: parseFloat($weight2point5kgs.val()),
    w1point25k: parseFloat($weight1point25kgs.val()),

  };

  localStorage.unitSystem = options.unitSystem;
  localStorage.barWeight = options.barWeight;
  localStorage.w100p = options.w100p;
  localStorage.w55p = options.w55p;
  localStorage.w45p = options.w45p;
  localStorage.w35p = options.w35p;
  localStorage.w25p = options.w25p;
  localStorage.w10p = options.w10p;
  localStorage.w5p = options.w5p;
  localStorage.w2point5p = options.w2point5p;
  localStorage.w50k = options.w50k;
  localStorage.w25k = options.w25k;
  localStorage.w20k = options.w20k;
  localStorage.w15k = options.w15k;
  localStorage.w10k = options.w10k;
  localStorage.w5k = options.w5k;
  localStorage.w2point5k = options.w2point5k;
  localStorage.w1point25k = options.w1point25k;

  console.log('Got options: ' + JSON.stringify(options));
  return options;
}

function getUnitSystem() {
  var tabs = document.getElementsByName("unit-tab");
  for (var t = 0; t < tabs.length; t++) {
    var tbclasses = tabs[t].className.split(" ");
    for ( var i = 0; i < tbclasses.length; i++) {
      if (tbclasses[i] === "active") {
        return t;
      }
    }
  }
}

function getBarbellWeight(unit, weight) {
  if (weight == "") {
    if (unit == 0 ) { return 45; } else { return 20; }
  } else { return weight; }
}

function getQueryParam(variable, defaultValue) {
  var query = location.search.substring(1);
  var vars = query.split('&');
  for (var i = 0; i < vars.length; i++) {
    var pair = vars[i].split('=');
    if (pair[0] === variable) {
      return decodeURIComponent(pair[1]);
    }
  }
  return defaultValue || false;
}
