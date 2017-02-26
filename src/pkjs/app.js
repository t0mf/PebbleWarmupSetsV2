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
      w100p: configData.w100p,
      w55p: configData.w55p,
      w45p: configData.w45p,
      w35p: configData.w35p,
      w25p: configData.w25p,
      w10p: configData.w10p,
      w5p: configData.w5p,
      w2point5p: configData.w2point5p,
      w50k: configData.w50k,
      w25k: configData.w25k,
      w20k: configData.w20k,
      w15k: configData.w15k,
      w10k: configData.w10k,
      w5k: configData.w5k,
      w2point5k: configData.w2point5k,
      w1point25k: configData.w1point25k
    }, function() {
      console.log('Send successful!');
    }, function() {
      console.log('Send failed!');
    });
  }
});