import { Injectable } from '@nestjs/common';
import axios from 'axios';
const api_url = "http://ergast.com/api/f1/" 
@Injectable()
export class CircuitsService{
    async getRandomCircuits():Promise<any>{
        const circuits = await this.getAllCircuits();
        const randomCircuits = this.chooseCircuits(circuits);
        return randomCircuits;
    }
    async getAllCircuits(){
        
        const response = await axios.get(api_url+'circuits.json?limit=1000');
        const circuits = this.extractCircuitsDetails(response.data.MRData.CircuitTable.Circuits);
        return circuits;
    }
    chooseCircuits(circuits:Array<any>):Array<any> {
        const randomCircuits = [];
        for (let i = 0; i < 3; i++) {
            const randomIndex = Math.floor(Math.random() * circuits.length);
            randomCircuits.push(circuits[randomIndex]);
            circuits.splice(randomIndex,1);
        }
        return randomCircuits;
    }
    extractCircuitsDetails(circuits:Array<any>):Array<any>{
        const circuits_details = [];
        for (const circuit of circuits) {
            const {circuitId ,url, circuitName,Location} = circuit;
            circuits_details.push({
                circuitId:circuitId,
                url:url,
                circuitName:circuitName,
                city:Location.locality,
                country:Location.country
            })
        }
        return circuits_details;
    }
}