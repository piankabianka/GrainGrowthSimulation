//DATA
const data = require('./drawGrid.js');

const stepButton=document.querySelector('#step');


stepButton.addEventListener('click', function(e){
    console.log(data.getData());
})