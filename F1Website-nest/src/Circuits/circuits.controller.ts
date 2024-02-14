import {Controller,Get} from '@nestjs/common';
import {CircuitsService} from './circuits.service';

@Controller('circuits')
export class CircuitsController {
    constructor(private readonly circuitsService: CircuitsService) {
    }
    @Get('/randomCircuits')
    async getRandomCircuits() {
        
        const circuits = await this.circuitsService.getRandomCircuits();
        return circuits;
    }
}