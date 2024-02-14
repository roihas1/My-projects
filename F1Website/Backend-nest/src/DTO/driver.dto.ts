import { IsString } from 'class-validator';

export class DriverDto {
    @IsString()
        driverId: string;

    @IsString()
        givenName: string;

    @IsString()
        familyName: string;

    @IsString()
        dateOfBirth: string;

    @IsString()
        nationality: string;
    @IsString()
        url: string;
    @IsString()
        about: string;



}

