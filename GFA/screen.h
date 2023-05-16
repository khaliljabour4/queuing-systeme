#include <Arduino.h>

const char screen_html[] PROGMEM = R"HTML(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@500&display=swap" rel="stylesheet">
    <style>
      * {
        box-sizing: border-box;
}
html,
body {
  margin: 0;
  height: 100%;
  width: 100%;
  overflow: hidden;
  position: relative;
}
/* body { */
/* display: grid;
    grid-template-columns: 3fr 2fr;
    grid-template-rows: 3fr 1fr;
    grid-template-areas:
      "video list"
      "news list"; */
/* } */
iframe,
#player {
  margin: 0;
  height: 100%;
  width: 100%;
  position: fixed;
  /* grid-area: video; */
}
.list {
  position: absolute;
  right: 0;
  grid-area: list;
  z-index: 1;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: flex-end;
  padding: 15px 10px;
  height: 100vh;
}
.list svg {
  flex-shrink: 1;
  flex-basis: 100%;
  max-width: 30vw;
}
.news {
  position: absolute;
  bottom: 0;
  z-index: 1;
  height: 30vh;
  padding: 20px;
}
.card {
  font-family: "Roboto";
  font-style: normal;
  display: flex;
  width: 100%;
  height: 100%;
  flex-direction: column;
  justify-content: center;
  align-items: flex-start;
  padding: 20px 30px;
  justify-content: space-around;
  background: linear-gradient(
      0deg,
      rgba(103, 80, 164, 0.14),
      rgba(103, 80, 164, 0.14)
    ),
    #fffbfe;
  box-shadow: 0px 8px 12px 6px rgba(0, 0, 0, 0.15),
    0px 4px 4px rgba(0, 0, 0, 0.3);
  border-radius: 16px;
}
.card h1,
.card h2 {
  margin: 0;
}
@keyframes blink {
  from {
    fill: rgb(103, 80, 164);
    fill-opacity: 0.14;
  }
  to {
    fill: rgb(255, 0, 0);
    fill-opacity: 0.5;
  }
}
.blink rect[fill="#6750A4"] {
  animation: blink 1s cubic-bezier(0, 0, 0.2, 1) 0s infinite alternate both;
}

.waiting {
  font-family: "Roboto";
  font-style: normal;
  display: flex;
  margin: auto;
  margin-top: 20px;
  justify-content: center;
  flex-direction: column;
  align-items: center;
}

.waiting-row {
  font-size: 1.5rem;
  max-width: 20rem;
  width: 90%;
  margin: .5rem;
}

.btn {
  height: 6rem;
  cursor: pointer;
}

    </style>
  </head>
  <body>
    <div class="list" id="list"></div>
    <div class="news" id="news">
        <div class="card">
            <h1 id="title">Title</h1>
            <h2 id="subtitle">SubTitle</h2>
        </div>
    </div>
    <div id="player"></div>
    <script type="text/javascript">
        var evtSource = new EventSource("/events");
var queues = []
var currentBlink = null
evtSource.onopen = function () {
    loadCounters();
}
evtSource.addEventListener('message',function (event) {
  console.log(event.data)
})
evtSource.addEventListener('queue',function (event) {
  var data = event.data.trim().split(' ')
  if(!queues[data[0]-1]){
    queues[data[0]-1] = addCounter()
    setCounter(queues[data[0]-1],data[0])
  }
  setQueue(queues[data[0]-1],data[1],true)
})
evtSource.addEventListener('rmqueue',function (event) {
  var data = parseInt(event.data.trim())
  removeCounter(data - 1)
})
var title = document.getElementById("title")
var subtitle = document.getElementById("subtitle")
evtSource.addEventListener('news',function (event) {
  var data = JSON.parse(event.data)
  title.textContent = data.title
  subtitle.textContent = data.subtitle
})
var list = document.getElementById("list")
var news = document.getElementById("news")

window.addEventListener('resize',onResize)
function onResize() {
    if (!list.children[0]) {
      news.style.width = '100%'
      return;
    }
    let w = (window.innerWidth - parseInt(window.getComputedStyle(list.children[0]).width))
    news.style.width = w + 'px'
}
onResize()
// 2. This code loads the IFrame Player API code asynchronously.
var tag = document.createElement('script');

tag.src = "https://www.youtube.com/iframe_api";
var firstScriptTag = document.getElementsByTagName('script')[0];
firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

// 3. This function creates an <iframe> (and YouTube player)
//    after the API code downloads.
var player;
// function getQueryVariable()
// {
//        var query = window.location.search.substring(1);
//        var vars = query.split("&");
//        var ret = {}
//        for (var i=0;i<vars.length;i++) {
//                var pair = vars[i].split("=");
//                ret[pair[0]] = pair[1]
//        }
//        return ret;
// }
function getQueryVariable(variable)
{
       var query = window.location.search.substring(1);
       var vars = query.split("&");
       for (var i=0;i<vars.length;i++) {
               var pair = vars[i].split("=");
               if(pair[0] == variable){return pair[1];}
       }
       return(false);
}
let obj = {}
let vid = getQueryVariable("videoId")
if(vid) obj.videoId = vid
obj.host = 'https://www.youtube-nocookie.com'
obj.playerVars = {
    'autoplay': 1,
    'playsinline': 1,
    'controls': 0,
    'loop': 1,
}
obj.onPlayerReady = function (event) {
  event.target.setPlaybackQuality('hd720');
}
obj.onPlayerStateChange = function (event) {
  if (event.data == YT.PlayerState.BUFFERING) {
      event.target.setPlaybackQuality('hd720');
  }
}
let pvid = getQueryVariable("playlist")
if(pvid) obj.playerVars.playlist = pvid
else if(vid) obj.playerVars.playlist = vid
function onYouTubeIframeAPIReady() {
  player = new YT.Player('player', obj);
}
evtSource.addEventListener('playvideo',function (event) {
  var data = event.data
  player.loadPlaylist(data)
})
evtSource.addEventListener('control',function (event) {
  var data = event.data.trim().split(' ')
  switch (data[0]) {
    case "pause":
      player.pauseVideo()
      break;
    case "play":
      player.playVideo()
      break;
    default:
      break;
  }
})
function openFullscreen() {
  if (document.body.requestFullscreen) {
    document.body.requestFullscreen();
  } else if (document.body.webkitRequestFullscreen) { /* Safari */
    document.body.webkitRequestFullscreen();
  } else if (document.body.msRequestFullscreen) { /* IE11 */
    document.body.msRequestFullscreen();
  }
}
window.onclick = openFullscreen
// 4. The API will call this function when the video player is ready.
// function onPlayerReady(event) {
//     window.addEventListener('click',function () {
//         event.target.playVideo();
//     })
// }

// 5. The API calls this function when the player's state changes.
//    The function indicates that when playing a video (state=1),
//    the player should play for six seconds and then stop.
// var done = false;
// function onPlayerStateChange(event) {
//   if (event.data == YT.PlayerState.PLAYING && !done) {
//     setTimeout(stopVideo, 6000);
//     done = true;
//   }
// }
// function stopVideo() {
//   player.stopVideo();
// }
function createElementFromHTML(htmlString) {
  var div = document.createElement('div');
  div.innerHTML = htmlString.trim();

  // Change this to div.childNodes to support multiple top-level nodes.
  return div.firstChild;
}
const d_html = createElementFromHTML(/*html*/`<svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 507 136"><g filter="url(#a)"><rect width="471" height="100" x="18" y="10" fill="#FFFBFE" rx="16"/><rect width="471" height="100" x="18" y="10" fill="#6750A4" fill-opacity=".14" rx="16"/><text xml:space="preserve" fill="#000" font-family="Roboto" font-size="48" font-weight="500" letter-spacing="0em" style="white-space:pre"><tspan x="56" y="76.406" class="n">001</tspan></text><text xml:space="preserve" fill="#21005D" font-family="Roboto" font-size="48" font-weight="500" letter-spacing="0em" style="white-space:pre"><tspan x="185" y="76.406" class="c">COUNTER 1</tspan></text></g><defs><filter id="a" width="507" height="136" x="0" y="0" color-interpolation-filters="sRGB" filterUnits="userSpaceOnUse"><feFlood flood-opacity="0" result="BackgroundImageFix"/><feColorMatrix in="SourceAlpha" result="hardAlpha" values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0"/><feOffset dy="4"/><feGaussianBlur stdDeviation="2"/><feColorMatrix values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.3 0"/><feBlend in2="BackgroundImageFix" result="effect1_dropShadow_6_38"/><feColorMatrix in="SourceAlpha" result="hardAlpha" values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0"/><feMorphology in="SourceAlpha" operator="dilate" radius="6" result="effect2_dropShadow_6_38"/><feOffset dy="8"/><feGaussianBlur stdDeviation="6"/><feColorMatrix values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.15 0"/><feBlend in2="effect1_dropShadow_6_38" result="effect2_dropShadow_6_38"/><feBlend in="SourceGraphic" in2="effect2_dropShadow_6_38" result="shape"/></filter></defs></svg>`)
function addCounter(id) {
  var clone = d_html.cloneNode(true)
  if(id) clone.id = id
  list.append(clone)
  onResize()
  return clone
}
function removeCounter(i) {
  list.removeChild(queues[i])
  queues[i] = null
  onResize()
}
function setCounter(el,c) {
  el.getElementsByClassName('c')[0].textContent = 'COUNTER '+String(c).padStart(2,'0')
}
var tout = null
function setQueue(el,n,blink) {
  el.getElementsByClassName('n')[0].textContent = String(n).charAt(0) + String(n).substring(1).padStart(3,'0')
  if(blink){
    clearTimeout(tout)
    for (var i = 0; i < queues.length; i++) {
      if(queues[i]) queues[i].className.baseVal = ""
    }
    el.className.baseVal = "blink"
    tout = setTimeout(function () {
      el.className.baseVal = ""
    },20*1000)
  }
}

function loadCounters() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var json = JSON.parse(xhttp.responseText);
        var len = json.length
        if(json.length < queues.length) len = queues.length
        for (var i = 0; i < len; i++) {
            var el = json[i];
            if(el == null){
              if(queues[i])
                removeCounter(i)
            }else{
              if(!queues[i]){
                  queues[i] = addCounter()
                  setCounter(queues[i],i+1)
              }
              setQueue(queues[i],el)
            }
        }
      }
  };
  xhttp.open("GET", "/api/counter", true);
  xhttp.send();
}
loadCounters()
function loadNews() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var json = JSON.parse(xhttp.responseText);
        title.textContent = json.title
        subtitle.textContent = json.subtitle
      }
  };
  xhttp.open("GET", "/api/news", true);
  xhttp.send();
}
loadNews()
evtSource.onopen = function () {
  loadNews()
  loadCounters()
}
    </script>
    <script type="module">
      import autoAnimate from "https://cdn.jsdelivr.net/npm/@formkit/auto-animate@1.0.0-beta.6/index.min.js"
      autoAnimate(document.getElementById("list"))
    </script>
</body>
</html>)HTML";
