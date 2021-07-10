{
	"description": "Daily statistics",
	"name": "SoftPowerStatistics",
	"properties": {
		"border_radius": "15px",
		"columns": 4,
		"hide_header": true,
		"row_height": 40,
		"show_template": true
	},
	"tabs": [
		{
			"icon": "fas fa-tachometer-alt",
			"name": "Solar Swiss Army Knife",
			"widgets": [
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "23h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 3,
						"row": 15,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 23h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "Yesterday",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 3,
						"row": 2,
						"sizeX": 1,
						"sizeY": 3
					},
					"panel": {
						"color": "#ffffff",
						"title": "Harvested  Yesterday"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 2,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "51px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "Today",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 2,
						"row": 2,
						"sizeX": 1,
						"sizeY": 3
					},
					"panel": {
						"color": "#ffffff",
						"title": "Harvested Today"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 2,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "51px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "00h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 0,
						"row": 5,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 0h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "01h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 1,
						"row": 5,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 1h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "02h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 2,
						"row": 5,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 2h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "06h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 2,
						"row": 7,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 6h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "05h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 1,
						"row": 7,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 5h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "04h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 0,
						"row": 7,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 4h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "03h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 3,
						"row": 5,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 3h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "10h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 2,
						"row": 9,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 10h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "09h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 1,
						"row": 9,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 9h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "08h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 0,
						"row": 9,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 8h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "07h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 3,
						"row": 7,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 7h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "14h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 2,
						"row": 11,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 14h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "13h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 1,
						"row": 11,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 13h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "12h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 0,
						"row": 11,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 12h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "11h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 3,
						"row": 9,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 11h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "18h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 2,
						"row": 13,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 18h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "17h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 1,
						"row": 13,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 17h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "16h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 0,
						"row": 13,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 16h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "15h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 3,
						"row": 11,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 15h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "22h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 2,
						"row": 15,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 22h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "21h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 1,
						"row": 15,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 21h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "20h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 0,
						"row": 15,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 20h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device_property": {
							"device": "SteroidsADS",
							"mapping": "19h",
							"property": "AhStat",
							"user": "KB5ZUR"
						},
						"source": "device_property"
					},
					"layout": {
						"col": 3,
						"row": 13,
						"sizeX": 1,
						"sizeY": 2
					},
					"panel": {
						"color": "#ffffff",
						"title": "Ah @ 19h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "32px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "Ah",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"bucket": {
							"backend": "dynamodb",
							"id": "HOUR",
							"mapping": [
								"Vin",
								"Vout",
								"Ahout"
							],
							"user": "KB5ZUR"
						},
						"source": "bucket"
					},
					"layout": {
						"col": 0,
						"row": 17,
						"sizeX": 4,
						"sizeY": 13
					},
					"panel": {
						"color": "#000000"
					},
					"properties": {
						"axis": true,
						"color": {
							"Ahout": "#fc8807",
							"Vin": "#fcf50a",
							"Vout": "#0afc15"
						},
						"fill": false,
						"legend": true,
						"multiple_axes": false,
						"timespan": {
							"magnitude": "day",
							"mode": "relative",
							"period": "latest",
							"value": 8
						},
						"xaxis": {
							"ticks": 12
						},
						"yaxis": {
							"max": 35,
							"min": -2,
							"ticks": 17
						}
					},
					"type": "chart"
				},
				{
					"data": {
						"device": {
							"id": "SteroidsADS",
							"interval": 60,
							"mapping": "BVDiff",
							"resource": "DAY",
							"update": "interval",
							"user": "KB5ZUR"
						},
						"source": "device"
					},
					"layout": {
						"col": 0,
						"row": 2,
						"sizeX": 1,
						"sizeY": 3
					},
					"panel": {
						"color": "#b6cfb1",
						"colors": [
							{
								"color": "#eef751",
								"max": -14,
								"min": -0.1
							},
							{
								"color": "#a3f394",
								"max": 14,
								"min": 0.1
							}
						],
						"title": "Voltage diff @ 24h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "51px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "V",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"device": {
							"id": "SteroidsADS",
							"interval": 60,
							"mapping": "BV@0h",
							"resource": "DAY",
							"update": "interval",
							"user": "KB5ZUR"
						},
						"source": "device"
					},
					"layout": {
						"col": 1,
						"row": 2,
						"sizeX": 1,
						"sizeY": 3
					},
					"panel": {
						"color": "#a5ee93",
						"colors": [
							{
								"color": "#bbf7be",
								"max": 14,
								"min": 12
							},
							{
								"color": "#e9ab74",
								"max": 12,
								"min": 11
							},
							{
								"color": "#fc520a",
								"max": 11,
								"min": 0
							},
							{
								"color": "#a806e6",
								"max": 15,
								"min": 14
							}
						],
						"title": "Voltage @ 24h"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 3,
						"gradient": true,
						"icon": "",
						"majorTicks": 1,
						"max": 1,
						"min": -1,
						"plateColor": "#ffffff",
						"showValue": true,
						"size": "51px",
						"textColor": "#1E313E",
						"tickColor": "#000000",
						"unit": "V",
						"unit_size": "20px",
						"weight": "font-thin"
					},
					"type": "text"
				},
				{
					"data": {
						"source": "value",
						"value": "Energy Statistics"
					},
					"layout": {
						"col": 0,
						"row": 0,
						"sizeX": 4,
						"sizeY": 2
					},
					"panel": {
						"color": "#dbdbdb"
					},
					"properties": {
						"color": "#1E313E",
						"decimal_places": 2,
						"icon": "",
						"size": "32px",
						"unit_size": "20px",
						"weight": "font-bold"
					},
					"type": "text"
				}
			]
		}
	]
}
