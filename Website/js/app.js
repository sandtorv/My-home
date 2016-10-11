var particle = new Particle();
var lastUpdated;

var months = ["January", "February", "March","April", "May", "June", "July","August", "September", "October","November", "December"];

var weekday = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"];

$(function() {
	console.log('Ready!');

  getObject();

  setInterval(function(){
    if(lastUpdated != undefined){
      $('#time').text("Last updated: " + timeSince(lastUpdated));
      var d = new Date();
      $('#clock').text(twoDecimals(d.getHours()) +':'+ twoDecimals(d.getMinutes()) +':'+twoDecimals(d.getSeconds()));
    }
  }, 1000);


});

function twoDecimals(number){
  console.log("number is: " + number);
  var l = number.toString().length;
  if(l == 0){
    return "00";
  } else if(l == 1){
    return "0"+number;
  } else {
    return number;
  }
}

function getObject(){
  particle.getVariable({ deviceId: deviceID, name: "object", auth: token }).then(function(data) {
    var obj = JSON.parse(data.body.result);
    updateView(obj);
    lastUpdated = data.body.coreInfo.last_heard;
  }, function(err) {
    console.log('An error occurred: ', err);
  });
}

function updateView(obj){
  $('#temp').text(obj.temp);
  $('#humid').text(obj.humid);
  $('#baro').text(obj.baro);
  updateProgress(obj.baro);
}

function updateProgress(progress){
  console.log("Progress " + progress);
  var percent = progress-960;
  console.log("Percent " + percent);
  $('.progress').width(percent + '%');
}

particle.getEventStream({ deviceId: deviceID, name: 'object', auth: token }).then(function(stream) {
  stream.on('event', function(data) {
    if(data.data != undefined){
      updateView(JSON.parse(data.data));
      lastUpdated = data.published_at;
    }
  });
});

function timeSince(date) {
  date = new Date(date);
  var seconds = Math.floor((new Date() - date) / 1000);
  var interval = Math.floor(seconds / 31536000);
  if (interval >= 1) {
    return interval + " year" + isMulti(interval);
  }
  interval = Math.floor(seconds / 2592000);
  if (interval >= 1) {
    return interval + " month" + isMulti(interval);
  }
  interval = Math.floor(seconds / 86400);
  if (interval >= 1) {
    return interval + " day" + isMulti(interval);
  }
  interval = Math.floor(seconds / 3600);
  if (interval >= 1) {
    return interval + " hour" + isMulti(interval);
  }
  interval = Math.floor(seconds / 60);
  if (interval >= 1) {
    return interval + " minute" + isMulti(interval);
  }
  var interval = Math.floor(seconds);
  return interval + " second" + isMulti(interval);
}

function isMulti(input){
  return input > 1 ? 's ago' : ' ago';
}