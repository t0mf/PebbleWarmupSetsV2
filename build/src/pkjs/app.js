Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://thomasfiveash.com/config-2/';

  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));

  console.log('Configuration page returned: ' + JSON.stringify(configData));

  if (configData) {
    Pebble.sendAppMessage({
      unitSystem: configData.unitSystem,
      barWeight: configData.barWeight,
      weight100lbs: configData.w100p,
      weight55lbs: configData.w55p,
      weight45lbs: configData.w45p,
      weight35lbs: configData.w35p,
      weight25lbs: configData.w25p,
      weight10lbs: configData.w10p,
      weight5lbs: configData.w5p,
      weight2point5lbs: configData.w2point5p,
      weight50kgs: configData.w50k,
      weight25kgs: configData.w25k,
      weight20kgs: configData.w20k,
      weight15kgs: configData.w15k,
      weight10kgs: configData.w10k,
      weight5kgs: configData.w5k,
      weight2point5kgs: configData.w2point5k,
      weight1point25kgs: configData.w1point25k
    }, function() {
      console.log('Send successful!');
    }, function() {
      console.log('Send failed!');
    });
  }
});