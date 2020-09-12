
//CANVAS
const canvas=document.querySelector('canvas');
canvas.width=window.innerWidth;
canvas.height=window.innerHeight-document.querySelector('#navigation').offsetHeight;
const c=canvas.getContext('2d');

//DATA

const submitButton=document.querySelector('#submit');

const nodesX=document.querySelector('#nodesX');
let nodesXValue=undefined;

const nodesY=document.querySelector('#nodesY');
let nodesYValue=undefined;

const cellSize=10;
const startPoint=10;
let endPointX=undefined
let endPointY=undefined;

const grains=document.querySelector('#grainsNumber');
let grainsNumber=undefined;

const kTParameter=document.querySelector('#kTParameter');
let kT=undefined;


//SUBMIT DATA
submitButton.addEventListener('click', function(e){
    e.preventDefault();

    nodesXValue=nodesX.querySelector('input[type="text"]').value;
    nodesYValue=nodesY.querySelector('input[type="text"]').value;
    endPointX=cellSize*nodesXValue;
    endPointY=cellSize*nodesYValue;
    grainsNumber=grains.querySelector('input[type="text"]').value;
    kT=kTParameter.querySelector('input[type="text"]').value;

    console.log(grainsNumber);
    console.log(kT);
    
    for(let i=0; i<=nodesXValue; i++){
        c.beginPath();
        c.moveTo(i*cellSize, startPoint);
        c.lineTo(i*cellSize, endPointY);
        c.strokeStyle="#C7D4CF";
        c.stroke();
    }
    
    for(let i=0; i<=nodesYValue; i++){
        c.beginPath();
        c.moveTo(startPoint, i*cellSize);
        c.lineTo(endPointX, i*cellSize);
        c.strokeStyle="#C7D4CF";
        c.stroke();
    }
})
    
    