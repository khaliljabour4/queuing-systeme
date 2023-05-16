#include <Arduino.h>
const char counter_html[] PROGMEM =  R"HTML(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Counter</title>
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@500&display=swap" rel="stylesheet">
    <style>
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
      .waiting-row {font-size: 24px;
        max-width: 320px;
        width: 90%;
        margin: 8px;
      }
      .btn {
        height: 96px;
        cursor: pointer;
      }
    </style>
    <link rel="stylesheet" href="style.css" />
  </head>
  <body>
    <div class="waiting">
      <div class="waiting-row">
        <span>Now Serving:</span>
        <svg
          xmlns="http://www.w3.org/2000/svg"
          fill="none"
          viewBox="0 0 507 136"
        >
          <g filter="url(#a)">
            <rect
              width="471"
              height="100"
              x="18"
              y="10"
              fill="#FFFBFE"
              rx="16"
            />
            <rect
              width="471"
              height="100"
              x="18"
              y="10"
              fill="#6750A4"
              fill-opacity=".14"
              rx="16"
            />
            <text
              xml:space="preserve"
              fill="#000"
              font-family="Roboto"
              font-size="48"
              font-weight="500"
              letter-spacing="0em"
              style="white-space: pre"
            >
              <tspan x="56" y="76.406" class="n" id="current">A000</tspan>
            </text>
            <text
              xml:space="preserve"
              fill="#21005D"
              font-family="Roboto"
              font-size="48"
              font-weight="500"
              letter-spacing="0em"
              style="white-space: pre"
            >
              <tspan x="185" y="76.406" class="c" id="counter">COUNTER 01</tspan>
            </text>
          </g>
          <defs>
            <filter
              id="a"
              width="507"
              height="136"
              x="0"
              y="0"
              color-interpolation-filters="sRGB"
              filterUnits="userSpaceOnUse"
            >
              <feFlood flood-opacity="0" result="BackgroundImageFix" />
              <feColorMatrix
                in="SourceAlpha"
                result="hardAlpha"
                values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0"
              />
              <feOffset dy="4" />
              <feGaussianBlur stdDeviation="2" />
              <feColorMatrix
                values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.3 0"
              />
              <feBlend
                in2="BackgroundImageFix"
                result="effect1_dropShadow_6_38"
              />
              <feColorMatrix
                in="SourceAlpha"
                result="hardAlpha"
                values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0"
              />
              <feMorphology
                in="SourceAlpha"
                operator="dilate"
                radius="6"
                result="effect2_dropShadow_6_38"
              />
              <feOffset dy="8" />
              <feGaussianBlur stdDeviation="6" />
              <feColorMatrix
                values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.15 0"
              />
              <feBlend
                in2="effect1_dropShadow_6_38"
                result="effect2_dropShadow_6_38"
              />
              <feBlend
                in="SourceGraphic"
                in2="effect2_dropShadow_6_38"
                result="shape"
              />
            </filter>
          </defs>
        </svg>
      </div>
      <div class="waiting-row">
        <span>Remaining in queue:</span>
        <svg
          xmlns="http://www.w3.org/2000/svg"
          fill="none"
          viewBox="0 0 507 136"
        >
          <g filter="url(#a)">
            <rect
              width="471"
              height="100"
              x="18"
              y="10"
              fill="#FFFBFE"
              rx="16"
            />
            <rect
              width="471"
              height="100"
              x="18"
              y="10"
              fill="#6750A4"
              fill-opacity=".14"
              rx="16"
            />
            <text
              xml:space="preserve"
              fill="#000"
              font-family="Roboto"
              font-size="48"
              font-weight="500"
              letter-spacing="0em"
              style="white-space: pre"
            >
              <tspan x="212.5" y="76.406" id="remaining">000</tspan>
            </text>
          </g>
          <defs>
            <filter
              id="a"
              width="507"
              height="136"
              x="0"
              y="0"
              color-interpolation-filters="sRGB"
              filterUnits="userSpaceOnUse"
            >
              <feFlood flood-opacity="0" result="BackgroundImageFix" />
              <feColorMatrix
                in="SourceAlpha"
                result="hardAlpha"
                values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0"
              />
              <feOffset dy="4" />
              <feGaussianBlur stdDeviation="2" />
              <feColorMatrix
                values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.3 0"
              />
              <feBlend
                in2="BackgroundImageFix"
                result="effect1_dropShadow_3_297"
              />
              <feColorMatrix
                in="SourceAlpha"
                result="hardAlpha"
                values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0"
              />
              <feMorphology
                in="SourceAlpha"
                operator="dilate"
                radius="6"
                result="effect2_dropShadow_3_297"
              />
              <feOffset dy="8" />
              <feGaussianBlur stdDeviation="6" />
              <feColorMatrix
                values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.15 0"
              />
              <feBlend
                in2="effect1_dropShadow_3_297"
                result="effect2_dropShadow_3_297"
              />
              <feBlend
                in="SourceGraphic"
                in2="effect2_dropShadow_3_297"
                result="shape"
              />
            </filter>
          </defs>
        </svg>
      </div>
      <svg
        class="btn"
        xmlns="http://www.w3.org/2000/svg"
        fill="none"
        viewBox="0 0 198 114"
        id="next"
      >
        <g filter="url(#a)">
          <g clip-path="url(#b)">
            <rect
              width="172.8"
              height="89.5"
              x="12.6"
              y="4"
              fill="#6750A4"
              rx="44.75"
            />
            <path
              fill="#fff"
              d="M86.057 37.104V59.25H82.24l-9.933-15.864V59.25H68.49V37.104h3.817L82.27 53V37.104h3.787Zm11.66 22.45c-1.216 0-2.316-.198-3.3-.593a7.287 7.287 0 0 1-2.494-1.688 7.483 7.483 0 0 1-1.567-2.54 8.893 8.893 0 0 1-.548-3.149v-.608c0-1.288.188-2.454.563-3.498.375-1.045.898-1.937 1.567-2.678a6.734 6.734 0 0 1 2.373-1.718 7.38 7.38 0 0 1 2.965-.593c1.177 0 2.206.197 3.088.593a5.806 5.806 0 0 1 2.19 1.673c.588.71 1.024 1.556 1.308 2.54.294.983.441 2.069.441 3.255v1.567H91.588v-2.632h9.096v-.289a5.17 5.17 0 0 0-.396-1.855 3.152 3.152 0 0 0-1.08-1.4c-.487-.355-1.135-.532-1.947-.532-.608 0-1.15.132-1.627.395a3.22 3.22 0 0 0-1.171 1.11c-.315.487-.558 1.076-.73 1.765-.163.68-.244 1.445-.244 2.297v.608c0 .72.096 1.39.29 2.008.202.608.496 1.14.881 1.597.386.456.852.816 1.4 1.08.547.253 1.17.38 1.87.38.883 0 1.668-.177 2.358-.532a5.4 5.4 0 0 0 1.795-1.506l1.932 1.87a7.537 7.537 0 0 1-1.385 1.491c-.567.467-1.262.847-2.083 1.141-.812.294-1.755.441-2.83.441Zm12.467-16.761 3.133 5.46 3.194-5.46h4.031l-4.989 8.076 5.187 8.381h-4.031l-3.346-5.688-3.346 5.688h-4.046l5.171-8.38-4.973-8.077h4.015Zm20.634 0v2.677h-9.278v-2.677h9.278Zm-6.601-4.03h3.666v15.94c0 .506.071.897.213 1.17.152.264.36.442.623.533.264.091.573.137.928.137.254 0 .497-.016.73-.046.233-.03.421-.06.563-.091l.015 2.798a9.377 9.377 0 0 1-1.064.244 7.824 7.824 0 0 1-1.369.106c-.842 0-1.587-.147-2.236-.44-.649-.305-1.156-.797-1.521-1.476-.365-.68-.548-1.582-.548-2.708V38.762Z"
            />
          </g>
        </g>
        <defs>
          <clipPath id="b">
            <rect
              width="172.8"
              height="89.5"
              x="12.6"
              y="4"
              fill="#fff"
              rx="44.75"
            />
          </clipPath>
          <filter
            id="a"
            width="196.8"
            height="113.5"
            x=".6"
            y="0"
            color-interpolation-filters="sRGB"
            filterUnits="userSpaceOnUse"
          >
            <feFlood flood-opacity="0" result="BackgroundImageFix" />
            <feColorMatrix
              in="SourceAlpha"
              result="hardAlpha"
              values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0"
            />
            <feOffset dy="8" />
            <feGaussianBlur stdDeviation="6" />
            <feComposite in2="hardAlpha" operator="out" />
            <feColorMatrix
              values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.15 0"
            />
            <feBlend
              in2="BackgroundImageFix"
              result="effect1_dropShadow_3_280"
            />
            <feColorMatrix
              in="SourceAlpha"
              result="hardAlpha"
              values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 127 0"
            />
            <feOffset dy="4" />
            <feGaussianBlur stdDeviation="2" />
            <feComposite in2="hardAlpha" operator="out" />
            <feColorMatrix values="0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.3 0" />
            <feBlend
              in2="effect1_dropShadow_3_280"
              result="effect2_dropShadow_3_280"
            />
            <feBlend
              in="SourceGraphic"
              in2="effect2_dropShadow_3_280"
              result="shape"
            />
          </filter>
        </defs>
      </svg>
    </div>
    <script>
      function getQueryVariable(variable) {
        var query = window.location.search.substring(1);
        var vars = query.split("&");
        for (var i = 0; i < vars.length; i++) {
          var pair = vars[i].split("=");
          if (pair[0] == variable) {
            return pair[1];
          }
        }
        return false;
      }
      let id = getQueryVariable("id");
      let r = document.getElementById("remaining");       //id for the number in the case line 172
      let c = document.getElementById("counter");        //!id for the counter number line 81
      let current = document.getElementById("current"); //id for the queue number line 70
      let remaining = 0;
      const letters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];
      c.textContent = `COUNTER ${String(Number(id)+1).padStart(2, '0')}`;
      setInterval(() => {
        fetch(`/api/stat?id=${id}`).then((res) => {
          res.json().then((data) => {
              remaining = data.remaining;
              r.textContent = String(data.remaining).padStart(3,'0');
              current.textContent = data.queue + String(data.current).padStart(3,'0');
          })
        })
      }, 1000);
      document.getElementById("next").addEventListener("click", () => {
  // !id for the button next
  if (remaining > 0) {
    fetch("/api/next", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        id,
      }),
    })
      .then((res) => res.json())
      .then((data) => {
        remaining = data.remaining;
        r.textContent = String(data.remaining).padStart(3, "0");
        current.textContent =
          data.queue + String(data.current).padStart(3, "0");
      });
  }
});
    </script>
  </body>
</html>)HTML";
