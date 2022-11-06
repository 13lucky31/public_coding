import requests

start_time = input('Enter start time (YYYY-MM-DD): ')
end_time = input('Enter end time (YYYY-MM-DD): ')
latitude = input('Enter latitude: ')
longitude = input('Enter longitude: ')
max_radius_km = input('Enter maxradiuskm: ')
min_magnitude = input('Enter minmagnitude: ')


url = 'https://earthquake.usgs.gov/fdsnws/event/1/query?'
response = requests.get(url, headers={'Accept': 'application/json'}, params={
        'format': 'geojson',
        'starttime': start_time,
        'endtime': end_time,
        'latitude': latitude,
        'longitude': longitude,
        'maxradiuskm': max_radius_km,
        'minmagnitude': min_magnitude
    })
data = response.json()
earthquake_list = data['features']
count = 0
print('\n-------> The places there was an earthquake in a given period of time: <-------\n')
for earthquake in earthquake_list:
        count += 1
        print(f'''{count}) Place: {earthquake['properties']['place']}. \nMinmagnitude: {earthquake['properties']['place']}.''')